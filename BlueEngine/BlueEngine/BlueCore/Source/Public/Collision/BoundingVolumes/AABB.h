#pragma once
#include "Core/Types.h"
#include "Core/Defines.h"
#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>
struct AABB
{
	bool IsZeroSized() { return glm::length2(halfExtents) == 0; }
	glm::vec3 position;
	glm::vec3 halfExtents;
};
