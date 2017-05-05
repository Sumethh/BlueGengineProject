#pragma once
#include "ForwardRenderer.h"
#include "DifferedRenderer.h"
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
	DifferedRenderer mDeferedRenderer;
};