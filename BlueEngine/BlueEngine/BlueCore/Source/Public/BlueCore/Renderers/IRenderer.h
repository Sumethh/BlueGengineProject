#pragma once
#include <glm/mat4x4.hpp>
#include "BlueCore/Core/CapturedPrimitiveData.h"
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
		virtual void SubmitGeometry(CapturedPrimitiveData& aPrimitiveData) = 0;
		virtual void SetActiveCamera(CapturedCameraData& aCamera) = 0;
		virtual void SetActiveLighting(SceneLighting* aLighting) = 0;
		virtual void SetActiveMaterial(Material* aMaterial) = 0;

		virtual void End() = 0;
	};
}