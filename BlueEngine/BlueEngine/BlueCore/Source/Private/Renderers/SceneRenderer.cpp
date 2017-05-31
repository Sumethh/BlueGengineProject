#include "Renderers/SceneRenderer.h"
#include "Core/Scene.h"
#include "Components/PrimitiveComponent.h"
#include "GraphicsDevice/IGraphicsDevice.h"
#include "Core/Timer.h"
#include <Imgui/imgui.h>
void SceneRenderer::ConductScenePass(Scene* aScene)
{
	IGraphicsDevice::GetCurrentGraphicsDevice()->ClearBuffer(BufferBit::DepthBit);

	const std::vector<PrimitiveComponent*>& primitives = aScene->GetAllPrimitives();
	Timer initTimer;
	initTimer.Start();
	sizeInt primitiveCount = primitives.size();
	std::vector<PrimitiveComponent*> translucentPrimitives;
	translucentPrimitives.reserve(primitiveCount);
	std::vector<PrimitiveComponent*> opaquePrimitives;
	opaquePrimitives.reserve(primitiveCount);
	ImGui::Text("Init Timer: %f ms", initTimer.IntervalMS());
	Timer sortingTimer;
	sortingTimer.Start();

	for (PrimitiveComponent* primitive : primitives)
	{
		//if (primitive->IsTranslucent())
		//{
		translucentPrimitives.push_back(primitive);
		//}
		//else
		//{
		//	opaquePrimitives.push_back(primitive);
		//}
	}

	ImGui::Text("Sorting Timer: %f ms", sortingTimer.IntervalMS());

	const std::vector<CameraComponent*>& cameras = aScene->GetAllCameras();

	//For every active camera cull objects
	//Run this over for each active camera? Should maybe also check for their viewport size
	Timer renderTimer;
	renderTimer.Start();


	for (CameraComponent* camera : cameras)
	{
		mForwardRenderer.SetActiveCamera(camera);

		OpaquePass(aScene, opaquePrimitives);
		TranslucentPass(aScene, translucentPrimitives);
	}

	mForwardRenderer.End();
	ImGui::Text("Render Timer: %f ms", renderTimer.IntervalMS());
}

void SceneRenderer::OpaquePass(Scene* aScene, std::vector<PrimitiveComponent*>& aOpaquePrimitives)
{
	//uses differed rendering
}

void SceneRenderer::TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives)
{
	//uses forward rendering
	for (PrimitiveComponent* primitive : aTranslucentPrimitives)
	{
		primitive->SubmitGeometry(&mForwardRenderer);
	}
}