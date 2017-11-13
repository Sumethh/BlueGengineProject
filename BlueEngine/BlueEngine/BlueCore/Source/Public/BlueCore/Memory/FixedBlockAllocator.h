#pragma once
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Core/Types.h"
#include "IMemoryAllocator.h"

namespace Blue
{
	struct Block;
	struct Page;

	class FixedBlockAllocator : public  IMemoryAllocator, public NonCopyable
	{
	public:
		FixedBlockAllocator(const int32 aPageSize, const int32* aBlockSizes, const int32 aBlockSizesCount);
		~FixedBlockAllocator() override;

		void* Allocate(size_t aSize, uint8 aAllignment) override;
		void Deallocate(void* aData, size_t aSize) override;
	private:

		float mMbUsed;
		float mMbAllocated;
		uint32 mFreeBlockCount;

		void Clear();
		Page* AllocateNewPage();

		static const int32 MaxBlockSizesCount = 25;

		const int32 mPageSize;
		const int32 mBlockSizesCount;
		int32 mBlockSizes[MaxBlockSizesCount];

		Page* mFirstPage;
		Page* mLastPage;

		Block* mFreeBlocks[MaxBlockSizesCount];
	};
}