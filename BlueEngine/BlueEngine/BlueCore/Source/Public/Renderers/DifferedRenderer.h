#pragma once
#include "IRenderer.h"


class DifferedRenderer : public IRenderer
{
	public:
	void End() override {};
	void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) override;
	void SetActiveCamera(CameraComponent* aCamera) override;
	void SetActiveMaterial(Material* aMaterial) override;
};
