#pragma once
#include "../Types.h"

namespace BlueGengine
{
	enum class EComponentType : uint32
	{
		ETransformComponent,
		EMeshComponent,
		EMaterialComponent,
		ECameraComponent,
		EFirstPersonComponent,
		ECount
	};
}