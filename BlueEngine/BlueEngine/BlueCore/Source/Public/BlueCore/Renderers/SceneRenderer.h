#pragma once
#include "ForwardRenderer.h"
#include "DefferedRenderer.h"

namespace Blue
{
	class Scene;
	class PrimitiveComponent;
	class SceneRenderer
	{
	public:
		void ConductScenePass(Scene* aScene);

	private:

		void OpaquePass(Scene* aScene, std::vector < PrimitiveComponent*>& aOpaquePrimitives);
		void TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives);

		ForwardRenderer mForwardRenderer;
		DefferedRenderer mDefferedRenderer;
	};
}