#pragma once
#include <vector>
#include "BlueCore/Core/Types.h"
namespace Blue
{
	template<typename T>

	class TPool
	{
	public:
		TPool(uint32 aInitialCount);
		TPool();
		~TPool();

		uint32 Allocate(T aNewObject);
		void Set(uint32 aIndex, T aObject);
		void Free(uint32 aIndex);

	private:
		std::vector<T> mPool;
		std::vector<uint32> mFreeIDs;
	};
}
