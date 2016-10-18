#pragma once
#include "Types.h"
#include <glm/glm.hpp>
namespace BlueGengine
{
	//TODO: Make sure that your provide the transposed inverse matrix for the to assure that non uniform scale lighting is correct
	class Shader;
	class Light
	{
	public:
		enum LightType
		{
			Direcitional,
			Point,
			Spotlight,
			Count
		};

		void TmpSetUp(Shader* a_shader);


		//private:
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 direction;
	};
}
