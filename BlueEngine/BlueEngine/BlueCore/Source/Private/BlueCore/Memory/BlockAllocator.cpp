#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Memory/BlockAllocator.h"
#include <new>


#define DEBUG_FREED_MEMORY 0xfdfd
#define DEBUG_ALLOCATED_MEMORY 0xacac
#define DEBUG_USED_MEMORY 0x0000
namespace Blue
{


	const int32 BlockAllocator::MaxBlockSizesCount;

	struct Page
	{
		uint32 pageSize;
		uint32 bytesUsed;
		uint32 bytesFree;
		Page* next;
		void* start;
	};
	struct Block
	{
		Block* next;
	};

	BlockAllocator::BlockAllocator(const int32 aPageSize, const int32* aBlockSizes, const int32 aBlockSizesCount) : IMemoryAllocator(), mFirstPage(nullptr), mPageSize(aPageSize), mBlockSizesCount(aBlockSizesCount)
	{
		BlueAssert(aBlockSizesCount <= MaxBlockSizesCount);
		for (int32 i = 0; i < mBlockSizesCount; ++i)
		{
			mBlockSizes[i] = aBlockSizes[i];
		}
		AllocateNewPage();
	}

	BlockAllocator::~BlockAllocator()
	{
		Clear();
	}

	void* BlockAllocator::Allocate(size_t aSize, uint8 aAllignment)
	{
		(void)aAllignment;
		BlueAssert(aSize > 0);
		if (aSize == 0)
			return nullptr;

		uint32 index = mBlockSizesCount;
		uint32 blockSize = 0;
		for (uint32 i = 0; i < mBlockSizesCount; ++i)
		{
			if (mBlockSizes[i] > aSize + sizeof(Block))
			{
				blockSize = mBlockSizes[i];
				index = i;
				break;
			}
		}

		if (index == mBlockSizesCount)
		{
			Log::Error("Could not allocate size as there is no valid block size. Tried to allocate Size: " + std::to_string(aSize));
			return nullptr;
		}

		++mNumAllocations;
		mUsedMemory += blockSize;

		if (mFreeBlocks[index])
		{
			Block* returningBlock = mFreeBlocks[index];
			mFreeBlocks[index] = returningBlock->next;

#ifdef _DEBUG
			ubyte* memory = reinterpret_cast<ubyte*>(returningBlock);
			memset(memory + sizeof(Block), DEBUG_USED_MEMORY, blockSize);
#endif
			return returningBlock;
		}

		Page* currentPage = mFirstPage;
		while (currentPage)
		{
			if (currentPage->bytesFree >= aSize)
			{
				break;
			}
			if (currentPage->next)
				currentPage = currentPage->next;
			else
			{
				currentPage->next = AllocateNewPage();
			}
		}

		ubyte* memory = static_cast<ubyte*>(currentPage->start) + currentPage->bytesUsed;
		currentPage->bytesUsed += blockSize;
		currentPage->bytesFree -= blockSize;
		Block* returningBlock = reinterpret_cast<Block*>(memory);
		returningBlock->next = nullptr;

#ifdef _DEBUG
		memset(memory + sizeof(Block), DEBUG_USED_MEMORY, blockSize);
#endif
		return returningBlock;
	}

	void BlockAllocator::Deallocate(void* aData, size_t aSize)
	{
		BlueAssert(aSize && aData);
		if (!aSize || !aData)
		{
			return;
		}

		--mNumAllocations;

		uint32 index = mBlockSizesCount;
		uint32 blockSize = 0;

		for (uint32 i = 0; i < mBlockSizesCount; ++i)
		{
			if (mBlockSizes[i] > aSize + sizeof(Block))
			{
				blockSize = mBlockSizes[i];
				index = i;
				break;
			}
		}

		mUsedMemory -= blockSize;

		if (index == mBlockSizesCount)
		{
			Log::Error("Could not deallocate size as there is no valid block size. Tried to allocate Size: " + std::to_string(aSize));
			return;
		}

		ubyte* memory = static_cast<ubyte*>(aData);
		Block* block = reinterpret_cast<Block*>(memory - sizeof(Block));

#ifdef _DEBUG
		Log::Info("Dealllocating" + std::to_string(aSize) + " block");
		memset(memory + sizeof(Block), DEBUG_FREED_MEMORY, blockSize);
#endif

		if (mFreeBlocks[index])
		{
			block->next = mFreeBlocks[index];
			mFreeBlocks[index] = block;
		}
		else
		{
			mFreeBlocks[index] = block;
		}
	}

	void BlockAllocator::Clear()
	{
		Page* currentPage = mFirstPage;
		while (currentPage)
		{
			Page* next = currentPage->next;
			delete currentPage;
			currentPage = next;
		}

		for (Block* block : mFreeBlocks)
		{
			block->next = nullptr;
		}
	}

	Page* BlockAllocator::AllocateNewPage()
	{
		ubyte* memory = static_cast<ubyte*>(malloc(mPageSize));
		Page* newPage = reinterpret_cast<Page*>(memory);

		newPage->pageSize = mPageSize;
		newPage->bytesFree = mPageSize - sizeof(Page);
		newPage->bytesUsed = sizeof(Page);
		newPage->next = nullptr;
		newPage->start = memory + sizeof(Page);

		if (!mFirstPage)
		{
			mFirstPage = newPage;
		}
#ifdef _DEBUG
		memset(newPage->start, DEBUG_ALLOCATED_MEMORY, mPageSize - sizeof(Page));
#endif
		return newPage;
	}
}