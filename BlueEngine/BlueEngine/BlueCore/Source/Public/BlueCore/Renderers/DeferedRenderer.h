#pragma once
#include "IRenderer.h"


namespace Blue
{
	class Shader;
	struct SceneLighting;
	class DeferedRenderer : public IRenderer
	{
	public:
		DeferedRenderer();
		~DeferedRenderer();
		void Init() override;

		void Begin();
		void End() override;

		void SubmitGeometry(CapturedPrimitiveData& aCapturedData) override;
		void SetActiveCamera(CapturedCameraData& aCamera) override;
		void SetActiveLighting(SceneLighting* aLighting) override;
		void SetActiveMaterial(Material* aMaterial) override;

	private:

		uint32 mFramebufferID;
		uint32 mDepthBufferID;
		uint32 mPositionTextureID;
		uint32 mColorSpecTextureID;
		uint32 mNormalTextureID;
		uint32 mQuadVbo;
		uint32 mQuadVao;

		CapturedCameraData mCurrentCameraData;
		glm::mat4 mCurrentProjectionMatrix;
		int32 mProjectionLocation;
		int32 mViewLocation;
		int32 mLightPassViewPosition;
		int32 mDirLightCountPosition;
		int32 mPointLightCountPosition;

		uint32 mModelLocation;
		GraphicsDeviceResourceID mCurrentBoundGrapicsID;
		Shader* mDeferedShader;
		Shader* mLightingPassShader;
		SceneLighting* mLighting;
	};
}