#pragma once
#include "IMemoryAllocator.h"
#include "Core/NonCopyable.h"

namespace Blue
{
	struct Block;
	class BlockAllocator : public IMemoryAllocator, public NonCopyable
	{
	public:
		BlockAllocator();
		~BlockAllocator();

		void* Allocate(size_t aSize, uint8 aAllignment) override;
		void DeAllocate(size_t aSize) override;
	private:
	};
}