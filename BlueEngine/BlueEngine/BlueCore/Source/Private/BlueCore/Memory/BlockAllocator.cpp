#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Memory/BlockAllocator.h"
#include <new>

#define DEBUG_FREED_MEMORY 0xfdfd
#define DEBUG_ALLOCATED_MEMORY 0xacac
#define DEBUG_USED_MEMORY 0x0000
namespace Blue
{


	const int32 BlockAllocator::BlockSizesCount;
	const int32 BlockAllocator::PageSize;


	const int32 BlockAllocator::BlockSizes[BlockSizesCount] =
	{
		32,  // 0
		64,  // 1
		96,  // 2
		128, // 3
		160, // 4
		192, // 5,
		224, // 6
		256, // 7
		320, // 8
		384, // 9
		448, // 10
		512, // 11
		576, // 12
		640, // 13
		704, // 14
		768, // 15
		832, // 16
		896, // 17
		960, // 18
		1024,// 19
	};

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

	BlockAllocator::BlockAllocator() : IMemoryAllocator(), mFirstPage(nullptr)
	{
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

		uint32 index = BlockSizesCount;
		uint32 blockSize = 0;
		for (uint32 i = 0; i < BlockSizesCount; ++i)
		{
			if (BlockSizes[i] > aSize + sizeof(Block))
			{
				blockSize = BlockSizes[i];
				index = i;
			}
		}
		if (index == BlockSizesCount)
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
			currentPage = currentPage->next;
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

		uint32 index = BlockSizesCount;
		uint32 blockSize = 0;

		for (uint32 i = 0; i < BlockSizesCount; ++i)
		{
			if (BlockSizes[i] > aSize + sizeof(Block))
			{
				blockSize = BlockSizes[i];
				index = i;
			}
		}

		mUsedMemory -= blockSize;

		if (index == BlockSizesCount)
		{
			Log::Error("Could not deallocate size as there is no valid block size. Tried to allocate Size: " + std::to_string(aSize));
			return;
		}

		ubyte* memory = static_cast<ubyte*>(aData);
		Block* block = reinterpret_cast<Block*>(memory - sizeof(Block));

#ifdef _DEBUG
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
		ubyte* memory = static_cast<ubyte*>(malloc(PageSize));
		Page* newPage = reinterpret_cast<Page*>(memory);

		newPage->pageSize = PageSize;
		newPage->bytesFree = PageSize - sizeof(Page);
		newPage->bytesUsed = sizeof(Page);
		newPage->next = nullptr;
		newPage->start = memory + sizeof(Page);

		if (!mFirstPage)
		{
			mFirstPage = newPage;
		}
		else
		{
			mLastPage->next = newPage;
			mLastPage = newPage;
		}
#ifdef _DEBUG
		memset(newPage->start, DEBUG_ALLOCATED_MEMORY, PageSize - sizeof(Page));
#endif
		return newPage;
	}

}