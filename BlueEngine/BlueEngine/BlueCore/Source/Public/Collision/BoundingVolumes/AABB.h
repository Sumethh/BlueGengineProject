#pragma once
#include "Core/Types.h"
#include "Core/Defines.h"
#include <glm/vec3.hpp>
namespace BlueCore
{
	struct AABB
	{
		glm::vec3 position;
		glm::vec3 halfExtents;
	};
};