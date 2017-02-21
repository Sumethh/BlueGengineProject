#pragma once
#include "Core/Types.h"
#include "Core/Defines.h"
#include <glm/vec3.hpp>

struct OBB
{
	glm::vec3 position;
	glm::vec3 halfExtents;
	glm::vec3 axes[3]; // x y z
};
