#pragma once
#include "IRenderer.h"


namespace Blue
{
	class DefferedRenderer : public IRenderer
	{
	public:
		void End() override {};
		void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) override;
		void SetActiveCamera(CameraComponent* aCamera) override;
		void SetActiveMaterial(Material* aMaterial) override;
	};
}