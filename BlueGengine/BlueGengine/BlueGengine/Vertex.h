#pragma once
#include <glm/glm.hpp>
#include "DataDescriptor.h"
namespace BlueGengine
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 biTangent;
	};

	static DataDescriptor sVertexDescriptors[5] =
	{
		{ 0, 3, sizeof(Vertex), 0, false, false, 0 },
		{ 1, 2, sizeof(Vertex), offsetof(Vertex, uv), false, false, 0 },
		{ 2, 3, sizeof(Vertex), offsetof(Vertex, normal), false, false, 0 },
		{ 3, 3, sizeof(Vertex), offsetof(Vertex, tangent), false, false, 0 },
		{ 4, 3, sizeof(Vertex), offsetof(Vertex, biTangent), false, false, 0 }
	};
	static uint32 sVertexDescriptorCount = 5;
}
