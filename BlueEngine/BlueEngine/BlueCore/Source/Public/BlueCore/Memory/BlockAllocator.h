#pragma once
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Core/Types.h"


#include "IMemoryAllocator.h"
namespace Blue
{
	struct Block;
	struct Page;

	class BlockAllocator : public IMemoryAllocator, public NonCopyable
	{
	public:
		BlockAllocator(const int32 aPageSize, const int32* aBlockSizes, const int32 aBlockSizesCount);
		~BlockAllocator() override;

		void* Allocate(size_t aSize, uint8 aAllignment) override;
		void Deallocate(void* aData, size_t aSize) override;
	private:

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