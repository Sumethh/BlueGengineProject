#include "BlueCore/Managers/MemoryManager.h"
#include "BlueCore/Hashing/CompileTimeHashing.h"
namespace Blue
{
	MemoryManager* MemoryManager::sInstance;
	const int32 SmallBlockAllocatorSizesCount = 25;
	const int32 SmallBlockAllocatorSizes[SmallBlockAllocatorSizesCount] =
	{
		8,   //0
		16,  //1
		32,  // 2
		64,  // 3
		96,  // 4
		128, // 5
		160, // 6
		192, // 7
		224, // 8
		256, // 9
		320, // 10
		384, // 11
		448, // 12
		512, // 13
		576, // 14
		640, // 15
		704, // 16
		768, // 17
		832, // 18
		896, // 19
		960, // 20
		1024,// 21
		1280, //22
		1536, //23
		2048, //24
	};
	const int32 SmallBlockAllocatorPageSize = 1000000;

	const int32 LargeBlockAllocatorSizesCount = 15;
	const int32 LargeBlockAllocatorSizes[LargeBlockAllocatorSizesCount] =
	{
		128000, //0
		192000, //1
		256000, //2
		320000, //3
		384000, //4
		448000, //5
		512000, //6
		576000, //7
		640000, //8
		704000, //9
		768000, //10
		832000, //11
		896000, //12
		960000, //13
		1024000,//14
	};
	const int32 LargeBlockAllocatorPageSize = 20000000;

	MemoryManager::MemoryManager() : mSmallBlockAllocator(SmallBlockAllocatorPageSize, SmallBlockAllocatorSizes, SmallBlockAllocatorSizesCount),
		mLargeBlockAllocator(LargeBlockAllocatorPageSize, LargeBlockAllocatorSizes, LargeBlockAllocatorSizesCount), 
		mRenderingAllocator(StaticHash("Rendering"))
	{

	}

}