#pragma once
#include "ForwardRenderer.h"
#include "DeferedRenderer.h"

namespace Blue
{
	class Scene;
	class PrimitiveComponent;
	class SceneRenderer
	{
	public:
		SceneRenderer();
		void ConductScenePass(Scene* aScene);

	private:

		void OpaquePass(Scene* aScene, std::vector < PrimitiveComponent*>& aOpaquePrimitives);
		void TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives);

		ForwardRenderer mForwardRenderer;
		DeferedRenderer mDefferedRenderer;
	};
}