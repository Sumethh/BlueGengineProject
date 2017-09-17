#pragma once
#include <glm/mat4x4.hpp>
namespace Blue
{
	class Mesh;
	class Material;
	class CameraComponent;
	struct SceneLighting;
	class IRenderer
	{
	public:
		virtual void Init() {};
		virtual void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) = 0;
		virtual void SetActiveCamera(CameraComponent* aCamera) = 0;
		virtual void SetActiveLighting(SceneLighting* aLighting) = 0;
		virtual void SetActiveMaterial(Material* aMaterial) = 0;

		virtual void End() = 0;
	};
}