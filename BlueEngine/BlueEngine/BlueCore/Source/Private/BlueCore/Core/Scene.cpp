#include "BlueCore/Core/Scene.h"

namespace Blue
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::RegisterPrimitiveComponent(PrimitiveComponent* aComponent)
	{
		mPrimitives.push_back(aComponent);
	}

	void Scene::RegisterLight(ILightComponent* aLight)
	{
		mLights.emplace_back(aLight);
	}

	void Scene::RegisterCamera(CameraComponent* aCamera)
	{
		mCameras.push_back(aCamera);
	}

	void Scene::DeregisterPimitiveComponent(PrimitiveComponent* aComponent)
	{
		std::vector<PrimitiveComponent*>::iterator foundComponent = std::find(mPrimitives.begin(), mPrimitives.end(), aComponent);

		if (foundComponent != mPrimitives.end())
		{
			mPrimitives.erase(foundComponent);
		}
	}

	void Scene::DeregisterLight(ILightComponent* aLight)
	{
		mLights.erase(std::find(mLights.begin(), mLights.end(), aLight));
	}

	void Scene::DeregisterCamera(CameraComponent* aCamera)
	{
		std::vector<CameraComponent*>::iterator foundCamera = std::find(mCameras.begin(), mCameras.end(), aCamera);

		if (foundCamera != mCameras.end())
		{
			mCameras.erase(foundCamera);
		}
	}
}