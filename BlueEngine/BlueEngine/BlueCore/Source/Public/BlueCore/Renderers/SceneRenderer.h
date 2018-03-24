#pragma once
#include "ForwardRenderer.h"
#include "DeferedRenderer.h"
#include "BlueCore/Graphics/RenderCommandBuffer.h"

namespace Blue
{
	class Scene;
	class PrimitiveComponent;
	class ILightComponent;

	struct SceneLighting
	{
		std::vector<ILightComponent*> lights;
	};

	class SceneRenderer
	{
	public:
		SceneRenderer();
		void Init();

		void CaptureScene(Scene* aScene);

		void ConductScenePass();
		
		static SceneRenderer* GI() {
			if (!sInstance)
				sInstance = new SceneRenderer();
			return sInstance;
		}

	private:

		static SceneRenderer* sInstance;

		void OpaquePass(std::vector<CapturedPrimitiveData>& aOpaquePrimitives, CapturedCameraData& aActiveCamera);
		void TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives, CameraComponent* aActiveCamera);

		ForwardRenderer mForwardRenderer;
		DeferedRenderer mDefferedRenderer;
		SceneLighting mLightingInfo;

		std::vector<CapturedPrimitiveData> mCapturedPrimitiveData;
		std::vector<CapturedCameraData> mCapturedCameraData;

		RenderCommandBuffer<uint64> DefferedCommandBuffer;
		RenderCommandBuffer<uint64> ForwardCommandBuffer;

	};
}