#pragma once
#include "Core/Types.h"

#include <glm/vec2.hpp>

namespace Blue
{
	class Viewport
	{
	public:
		//Values must be between 0-1
		void SetDimensions(glm::vec2 aDimensions)
		{
			mDimensions = aDimensions;
		}
		//must be
		void SetPosition(glm::vec2 aPosition)
		{
			mPosition = aPosition;
		}
	private:
		glm::vec2 mDimensions;
		glm::vec2 mPosition;
	};
}