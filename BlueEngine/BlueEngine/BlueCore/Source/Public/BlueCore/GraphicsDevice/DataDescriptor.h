#pragma once
#include "BlueCore/Core/Types.h"

namespace Blue
{
	struct DataDescriptor
	{
		uint32 location;
		uint32 count;
		uint32 stride;
		uint32 offset;
		bool normalized;

		bool instanced;
		uint32 instanceCount;
	};
}