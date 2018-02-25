#pragma once
#include "BlueCore/BlueCore.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Core/Transformable.h"
#include <glm/mat4x4.hpp>

namespace Blue
{
	class GraphicsResource;

	struct CapturedCameraData
	{
		Transform cameraTransform;
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
	};


	struct CapturedPrimitiveData
	{
		GraphicsDeviceResourceID meshResourceToBind = 0;
		EDrawMode drawMode = EDrawMode::Triangles;
		uint32 indexCount = 0;
		uint32 vertexCount = 0;

		GraphicsResource* diffuseTexture = nullptr;
		glm::mat4 modelMatrix;
	};
}