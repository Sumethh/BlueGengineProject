#include "BlueCore/Memory/TaggedPageAllocator.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Managers/DebugManager.h"

namespace Blue
{
	const uint32 MegaByte = 1000000;
	const int32 TaggedPageAllocator::sPageSize = 2000000;
	const uint32 PageMegaByteSize = TaggedPageAllocator::sPageSize / MegaByte;

	TaggedPageAllocator::TaggedPageAllocator()
	{
		BEGIN_DEBUG_GROUP("Memory/TaggedPagedAllocator");
		ADD_DEBUG_WATCHABLE(mPagesTotal);
		ADD_DEBUG_WATCHABLE(mPagesAllocated);
		ADD_DEBUG_WATCHABLE(mPagesFree);
		ADD_DEBUG_WATCHABLE(mMbytesTotal);
		ADD_DEBUG_WATCHABLE(mMbytesUsed);
		ADD_DEBUG_WATCHABLE(mMbFree);
		END_DEBUG_GROUP();
	}

	TaggedPageAllocator::~TaggedPageAllocator()
	{
		for (auto iter : mAllocatedPages)
		{
			DeallocateTag(iter.first);
		}

		void* page = nullptr;
		while(mFreePages.size())
		{
			page = mFreePages.front();
			mFreePages.pop();
			free(page);
		}

		mFreePages.empty();
	}

	void* TaggedPageAllocator::AllocatePage(uint64 aTag, void* aReturningPage)
	{
		std::lock_guard<std::mutex> lock(mAllocationMutex);

		if (aReturningPage)
		{
			mAllocatedPages[aTag].emplace_back(aReturningPage);
		}

		void* returningPage = nullptr;
		
		if (!mFreePages.empty())
		{
			returningPage = mFreePages.front();
			mFreePages.pop();
			--mPagesFree;
			mMbFree -= PageMegaByteSize;
		}
		else
		{
			void* newPage = malloc(sPageSize);
			BlueAssert(newPage);			
			returningPage = newPage;
			++mPagesTotal;
			++mPagesAllocated;
			mMbytesTotal += PageMegaByteSize;
		}
		mMbytesUsed += PageMegaByteSize;
		return returningPage;
	}

	void TaggedPageAllocator::DeallocateTag(uint64 aTag)
	{
		std::lock_guard<std::mutex> lock(mAllocationMutex);

		auto foundIterator = mAllocatedPages.find(aTag);
		if (foundIterator != mAllocatedPages.end())
		{
			std::vector<void*>& listOfPages = foundIterator->second;
			for (void* page : listOfPages)
			{
				mFreePages.push(page);

				mMbFree += PageMegaByteSize;
				++mPagesFree;
				--mPagesAllocated;
			}
			listOfPages.clear();
		}
	}

}