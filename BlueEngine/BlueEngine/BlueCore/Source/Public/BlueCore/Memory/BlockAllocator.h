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
		BlockAllocator();
		~BlockAllocator() override;

		void* Allocate(size_t aSize, uint8 aAllignment) override;
		void Deallocate(void* aData, size_t aSize) override;
	private:

		void Clear();
		Page* AllocateNewPage();

		static const int32 BlockSizesCount = 20;
		static const int32 BlockSizes[BlockSizesCount];
		static const int32 PageSize = 2000000;

		Page* mFirstPage;
		Page* mLastPage;

		Block* mFreeBlocks[BlockSizesCount];
	};
}