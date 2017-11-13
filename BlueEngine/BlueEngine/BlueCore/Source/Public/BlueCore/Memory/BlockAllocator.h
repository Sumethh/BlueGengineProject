#pragma once
#include "IMemoryAllocator.h"
#include <mutex>

namespace Blue
{
	class BlockAllocator : IMemoryAllocator
	{
		struct Page
		{
			uint32 bytesUsed;
			uint32 bytesFree;
			Page* next;
			byte* start;
		};
		struct Block
		{
			uint32 size;
			Block* next;
		};

	public:

		BlockAllocator();
		~BlockAllocator();

		void* Allocate(size_t aSize, uint8 aAllignment) override;
		void Deallocate(void* aData, size_t aSize) override;

		void Defragment();

	private:

		Page* AllocatePage();
		Page* FindPageWithSpace(sizeInt aSize);
		Block* FindAndRemoveFreeBlock(sizeInt aSize);
		Page* mPages;
		Block* mFreeBlocks;

		std::mutex mMutex;

		static const sizeInt sPageSize = 20000000;
		static const sizeInt sMinBlockSize = 32;
		static const sizeInt sMinSizeDifferenceForSplit = 32;
	};
}
