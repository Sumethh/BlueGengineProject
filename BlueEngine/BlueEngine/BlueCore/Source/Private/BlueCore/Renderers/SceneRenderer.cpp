#include "BlueCore/Renderers/SceneRenderer.h"
#include "BlueCore/Core/Scene.h"
#include "BlueCore/Components/PrimitiveComponent.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Graphics/RenderThread.h"
#include "BlueCore/Core/Timer.h"
#include <Imgui/imgui.h>

namespace Blue
{
	SceneRenderer* SceneRenderer::sInstance = nullptr;
	SceneRenderer::SceneRenderer()
	{
	}

	void SceneRenderer::Init()
	{
		mForwardRenderer.Init();
		mDefferedRenderer.Init();
	}

	void SceneRenderer::CaptureScene(Scene* aScene)
	{
		BlueAssert(aScene && RenderThread::IsOnRenderThread());

		mCapturedPrimitiveData.clear();
		mCapturedCameraData.clear();
		IGraphicsDevice::GetCurrentGraphicsDevice()->ClearBuffer(EBufferBit::DepthBit);

		aScene->AquireSceneLock();
		const std::vector<PrimitiveComponent*>& primitives = aScene->GetAllPrimitives();
		const std::vector<CameraComponent*>& cameras = aScene->GetAllCameras();
		const std::vector<ILightComponent*>& lights = aScene->GetAllLights();

		mCapturedCameraData.reserve(primitives.size());

		for (CameraComponent* camera : cameras)
		{
			camera->CaptureData(mCapturedCameraData.emplace_back(CapturedCameraData()));
		}

		for (PrimitiveComponent* primitive : primitives)
		{
			primitive->SubmitGeometry(mCapturedPrimitiveData.emplace_back(CapturedPrimitiveData()));
		}

		aScene->ReleaseSceneLock();
	}
	
	void SceneRenderer::ConductScenePass()
	{
		BlueAssert(RenderThread::IsOnRenderThread());
		
		for (CapturedCameraData& cameraData : mCapturedCameraData)
		{
			OpaquePass(mCapturedPrimitiveData, cameraData);
		}
	}

	void SceneRenderer::OpaquePass(std::vector<CapturedPrimitiveData>& aOpaquePrimitives, CapturedCameraData& aActiveCamera)
	{
		mDefferedRenderer.Begin();
		mDefferedRenderer.SetActiveCamera(aActiveCamera);
		for (CapturedPrimitiveData& capturedData : aOpaquePrimitives)
		{
			mDefferedRenderer.SubmitGeometry(capturedData);
		}
		mDefferedRenderer.End();
	}

	void SceneRenderer::TranslucentPass(Scene* aScene, std::vector<PrimitiveComponent*>& aTranslucentPrimitives, CameraComponent* aActiveCamera)
	{
	}
}