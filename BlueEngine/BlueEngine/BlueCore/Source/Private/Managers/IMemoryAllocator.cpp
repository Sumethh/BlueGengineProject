#include "Memory/IMemoryAllocator.h"

IMemoryAllocator::IMemoryAllocator(sizeInt aSize, void* aStart): mStart(aStart), mUsedMemory(0),
				 mNumAllocations(0), mSize(aSize)
{

}

IMemoryAllocator::~IMemoryAllocator()
{
	BlueAssert(mNumAllocations == 0 && mUsedMemory ==  0);

	mStart = nullptr;
	mSize = 0;
}