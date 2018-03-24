#pragma once
#include "UpdateableManager.h"

#include "BlueCore/Memory/FixedBlockAllocator.h"
#include "BlueCore/Memory/TaggedBlockAllocator.h"

namespace Blue
{
	class MemoryManager
	{
	public:
		MemoryManager();
		~MemoryManager() = default;

		static MemoryManager* GI()
		{
			if (!sInstance)
			{
				sInstance = new MemoryManager();
			}
			return sInstance;
		}

		static void DeleteInstance()
		{
			if (sInstance)
				delete sInstance;
		}

		IMemoryAllocator* GetSmallBlockAllocator()
		{
			return &mSmallBlockAllocator;
		}
		IMemoryAllocator* GetLargeBlockAllocator()
		{
			return &mLargeBlockAllocator;
		}

		TaggedPageAllocator* GetTaggedPageAllocator()
		{
			return &mTaggedPageAllocator;
		}

		TaggedBlockAllocator* GetRenderingAllocator()
		{
			return &mRenderingAllocator;
		}

	private:
		static MemoryManager* sInstance;
		FixedBlockAllocator mSmallBlockAllocator;
		FixedBlockAllocator mLargeBlockAllocator;

		TaggedPageAllocator mTaggedPageAllocator;

		TaggedBlockAllocator mRenderingAllocator;
	};


	template <typename T,typename... Args>
	T* CreateNewObject(Args... aArgs) 
	{
		IMemoryAllocator* smallMemoryAllocator = MemoryManager::GI()->GetSmallBlockAllocator();
		BlueAssert(smallMemoryAllocator && sizeof(T) < smallMemoryAllocator->GetLargestAllocationSize());
		byte* memory = static_cast<byte*>(smallMemoryAllocator->Allocate(sizeof(T), 8));
		return new(memory) T(aArgs...);
	};

	template<typename T>
	void DeleteObject(T* aObjectToDelete)
	{
		IMemoryAllocator* smallMemoryAllocator = MemoryManager::GI()->GetSmallBlockAllocator();
		smallMemoryAllocator->Deallocate(static_cast<void*>(aObjectToDelete), sizeof(T));
	}

}