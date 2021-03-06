#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"
#include <glm/vec3.hpp>
#include <glm/gtx/norm.hpp>

namespace Blue
{
	struct AABB
	{
		bool IsZeroSized()
		{
			return glm::length2(halfExtents) == 0;
		}
		glm::vec3 position;
		glm::vec3 halfExtents;
	};
}