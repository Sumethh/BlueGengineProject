#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"
#include <glm/vec3.hpp>

namespace Blue
{
	struct OBB
	{
		glm::vec3 position;
		glm::vec3 halfExtents;
		glm::vec3 axes[3]; // x y z
	};
}