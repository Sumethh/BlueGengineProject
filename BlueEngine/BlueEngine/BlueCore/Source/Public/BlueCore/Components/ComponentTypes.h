#pragma once
#include "BlueCore/Core/Types.h"

namespace Blue
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

	static const char* EComponentTypeStrings[] =
	{
		"Transform Component",
		"Mesh Component",
		"Material Component",
		"Camera Component",
		"First Person Component"
	};
}