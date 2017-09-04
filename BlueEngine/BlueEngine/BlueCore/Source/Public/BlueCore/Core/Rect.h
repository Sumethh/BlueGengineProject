#pragma once
#include <glm/vec2.hpp>

namespace Blue
{
	struct Rect
	{
		glm::vec2 topLeft;
		glm::vec2 extents;
	};
	struct IntRect
	{
		IntRect() = default;
		IntRect(const Rect& aRect) : topLeft(aRect.topLeft), extents(aRect.extents)
		{}
		glm::ivec2 topLeft;
		glm::ivec2 extents;
	};
}