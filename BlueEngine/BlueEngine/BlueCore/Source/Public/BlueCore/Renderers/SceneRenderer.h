#pragma once
#include "ForwardRenderer.h"
#include "DeferedRenderer.h"

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
		void ConductScenePass(Scene* aScene);

	private:

		void OpaquePass(Scene* aScene, std::vector<PrimitiveComponent*>& aOpaquePrimitives, CameraComponent* aActiveCamera);
		void TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives, CameraComponent* aActiveCamera);

		ForwardRenderer mForwardRenderer;
		DeferedRenderer mDefferedRenderer;
		std::vector<PrimitiveComponent*> mTranslucentPrimitives;
		std::vector<PrimitiveComponent*> mOpaquePrimitives;
		SceneLighting mLightingInfo;
	};
}