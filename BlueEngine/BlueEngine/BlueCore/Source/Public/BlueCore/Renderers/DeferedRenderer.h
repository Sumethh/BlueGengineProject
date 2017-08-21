#pragma once
#include "IRenderer.h"


namespace Blue
{
	class DeferedRenderer : public IRenderer
	{
	public:
		DeferedRenderer();
		~DeferedRenderer();
		void Init() override;
		void End() override {};
		void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) override;
		void SetActiveCamera(CameraComponent* aCamera) override;
		void SetActiveMaterial(Material* aMaterial) override;

	private:
		uint32 mFramebufferID;
		uint32 mDepthBufferID;
		uint32 mPositionTextureID;
		uint32 mColorSpecTextureID;
		uint32 mNormalTextureID;
	};
}