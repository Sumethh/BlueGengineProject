#pragma once
#include <unordered_map>
#include "../Components/TransformComponent.h"
namespace BlueCore
{
	class Mesh;
	class Material;
	class CameraComponent;
	class BLUECORE_API IRenderer
	{
		public:

		virtual void SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform) = 0;
		virtual void SubmitCamera(CameraComponent* aCamera) = 0;
		virtual void Flush() = 0;
	};
}