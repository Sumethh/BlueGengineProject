#pragma once
#include "UpdateableManager.h"

#include "BlueCore/Memory/BlockAllocator.h"

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

		BlockAllocator& GetSmallBlockAllocator()
		{
			return mSmallBlockAllocator;
		}
		BlockAllocator& GetLargeBlockAllocator()
		{
			return mLargeBlockAllocator;
		}

	private:
		static MemoryManager* sInstance;
		BlockAllocator mSmallBlockAllocator;
		BlockAllocator mLargeBlockAllocator;
	};
}