#pragma once
#include "UpdateableManager.h"

#include "BlueCore/Memory/FixedBlockAllocator.h"

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

		FixedBlockAllocator& GetSmallBlockAllocator()
		{
			return mSmallBlockAllocator;
		}
		FixedBlockAllocator& GetLargeBlockAllocator()
		{
			return mLargeBlockAllocator;
		}

	private:
		static MemoryManager* sInstance;
		FixedBlockAllocator mSmallBlockAllocator;
		FixedBlockAllocator mLargeBlockAllocator;
	};
}