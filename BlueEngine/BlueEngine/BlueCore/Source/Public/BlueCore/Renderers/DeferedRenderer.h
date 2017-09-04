#pragma once
#include "IRenderer.h"


namespace Blue
{
	class Shader;
	class DeferedRenderer : public IRenderer
	{
	public:
		DeferedRenderer();
		~DeferedRenderer();
		void Init() override;

		void Begin();
		void End();

		void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) override;
		void SetActiveCamera(CameraComponent* aCamera) override;
		void SetActiveMaterial(Material* aMaterial) override;

	private:

		uint32 mFramebufferID;
		uint32 mDepthBufferID;
		uint32 mPositionTextureID;
		uint32 mColorSpecTextureID;
		uint32 mNormalTextureID;
		uint32 mQuadVbo;
		uint32 mQuadVao;


		Material* mCurrentMaterial;
		CameraComponent* mCurrentCamera;
		glm::mat4 mCurrentProjectionMatrix;
		int32 mProjectionLocation;
		int32 mViewLocation;
		int32 mLightPassViewPosition;
		int32 mDirLightCountPosition;
		int32 mPointLightCountPosition;

		uint32 mModelLocation;
		Mesh* mCurrentMesh;
		Shader* mDeferedShader;
		Shader* mLightingPassShader;
	};
}