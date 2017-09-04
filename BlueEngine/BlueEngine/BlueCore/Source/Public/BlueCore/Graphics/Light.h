#pragma once
#include "BlueCore/Core/Types.h"
#include <glm/glm.hpp>


namespace Blue
{
	//TODO: Make sure that your provide the transposed inverse matrix for the to assure that non uniform scale lighting is correct
	class Shader;
	struct PointLight
	{
		float radius;
		glm::vec3 position;
		glm::vec3 color;
	};
}