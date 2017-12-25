#include "BlueCore/Memory/BlockAllocator.h"
#include "BlueCore/Core/Defines.h"

namespace Blue
{
	const sizeInt BlockAllocator::sPageSize;
	const sizeInt BlockAllocator::sMinBlockSize;
	const sizeInt BlockAllocator::sMinSizeDifferenceForSplit;


	BlockAllocator::BlockAllocator() : mPages(AllocatePage()), mFreeBlocks(nullptr)
	{

	}

	BlockAllocator::~BlockAllocator()
	{
		Page* currentPage = mPages;
		while (currentPage)
		{
			Page* nextPage = currentPage->next;
			delete currentPage;
			currentPage = nextPage;
		}
	}

	void* BlockAllocator::Allocate(size_t aSize, uint8 aAllignment)
	{
		BlueAssert(aSize < sPageSize);

		Block* foundBlock = FindAndRemoveFreeBlock(aSize);
		if (foundBlock)
		{
			return reinterpret_cast<void*>(foundBlock + 1);
		}
		Page* foundPage = FindPageWithSpace(aSize + sizeof(Block));
		BlueAssert(foundPage);

		foundBlock = reinterpret_cast<Block*>(foundPage->start + foundPage->bytesUsed);
		foundBlock->size = static_cast<uint32>(aSize);

		foundPage->bytesUsed += sizeof(Block) + aSize;
		foundPage->bytesFree -= sizeof(Block) + aSize;

		return (void*)(foundBlock + 1);
	}

	void BlockAllocator::Deallocate(void* aData, size_t aSize)
	{

	}

	void BlockAllocator::Defragment()
	{
		//Dont forget to add the size of the block to the block size when combining
	}

	BlockAllocator::Page* BlockAllocator::AllocatePage()
	{
		Page* newPage = (Page*)malloc(sPageSize);
		newPage->bytesFree = sPageSize - sizeof(Page);
		newPage->bytesUsed = 0;
		newPage->next = nullptr;
		newPage->start = reinterpret_cast<byte*>(newPage + 1);
		return newPage;
	}

	BlockAllocator::Page* BlockAllocator::FindPageWithSpace(sizeInt aSize)
	{
		Page* currentPage = mPages;
		Page* previousPage = nullptr;
		while (currentPage)
		{
			if (currentPage->bytesFree >= aSize)
			{
				return currentPage;
			}
			previousPage = currentPage;
			currentPage = currentPage->next;
		}
		BlueAssert(!currentPage && previousPage);
		Page* newPage = AllocatePage();
		previousPage->next = newPage;
		return newPage;
	}

	BlockAllocator::Block* BlockAllocator::FindAndRemoveFreeBlock(sizeInt aSize)
	{
		Block* currentBlock = mFreeBlocks;
		while (currentBlock)
		{
			if (currentBlock->size >= aSize)
				break;
			currentBlock = currentBlock->next;
		}

		if (currentBlock)
		{
			const sizeInt blockSize = currentBlock->size;

		}
		return nullptr;
	}

}