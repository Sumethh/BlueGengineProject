#pragma once
#include "Core/Types.h"
namespace BlueCore
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