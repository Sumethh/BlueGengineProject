#include "BlueCore/Renderers/SceneRenderer.h"
#include "BlueCore/Core/Scene.h"
#include "BlueCore/Components/PrimitiveComponent.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Core/Timer.h"
#include <Imgui/imgui.h>

namespace Blue
{

	SceneRenderer::SceneRenderer()
	{
		mForwardRenderer.Init();
		mDefferedRenderer.Init();
	}

	void SceneRenderer::ConductScenePass(Scene* aScene)
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->ClearBuffer(EBufferBit::DepthBit);

		const std::vector<PrimitiveComponent*>& primitives = aScene->GetAllPrimitives();
		Timer initTimer;
		initTimer.Start();
		sizeInt primitiveCount = primitives.size();
		ImGui::Text("Init Timer: %f ms", initTimer.IntervalMS());
		Timer sortingTimer;
		sortingTimer.Start();

		for (PrimitiveComponent* primitive : primitives)
		{
			if (primitive->IsTranslucent())
			{
				mTranslucentPrimitives.push_back(primitive);
			}
			else
			{
				mOpaquePrimitives.push_back(primitive);
			}
		}

		ImGui::Text("Sorting Timer: %f ms", sortingTimer.IntervalMS());

		const std::vector<CameraComponent*>& cameras = aScene->GetAllCameras();

		//For every active camera cull objects
		//Run this over for each active camera? Should maybe also check for their viewport size
		Timer renderTimer;
		renderTimer.Start();


		for (CameraComponent* camera : cameras)
		{
			OpaquePass(aScene, mOpaquePrimitives, camera);
			TranslucentPass(aScene, mOpaquePrimitives, camera);
		}
		mOpaquePrimitives.clear();
		mTranslucentPrimitives.clear();
		ImGui::Text("Render Timer: %f ms", renderTimer.IntervalMS());
	}

	void SceneRenderer::OpaquePass(Scene* aScene, std::vector<PrimitiveComponent*>& aOpaquePrimitives, CameraComponent* aActiveCamera)
	{
		mDefferedRenderer.Begin();
		mDefferedRenderer.SetActiveCamera(aActiveCamera);
		for (PrimitiveComponent* primitive : aOpaquePrimitives)
		{
			primitive->SubmitGeometry(&mDefferedRenderer);
		}
		mDefferedRenderer.End();
	}

	void SceneRenderer::TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives, CameraComponent* aActiveCamera)
	{
		return;
		mForwardRenderer.SetActiveCamera(aActiveCamera);
		//uses forward rendering
		for (PrimitiveComponent* primitive : aTranslucentPrimitives)
		{
			primitive->SubmitGeometry(&mForwardRenderer);
		}
		mForwardRenderer.End();
	}
}