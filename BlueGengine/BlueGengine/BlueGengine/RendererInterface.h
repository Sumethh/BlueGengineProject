#pragma once
#include <unordered_map>
#include "Components/TransformComponent.h"
namespace BlueGengine
{
	class Mesh;
	class Material;
	class CameraComponent;
	class IRenderer
	{
		public:

		virtual void SubmitMesh(Mesh* a_mesh, Material* a_material, Transform a_transform) = 0;
		virtual void SubmitCamera(CameraComponent* a_camera) = 0;
		virtual void Flush() = 0;
	};
}