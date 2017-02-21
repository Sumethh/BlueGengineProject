#include "Core/Scene.h"


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

void Scene::RegisterLight(LightComponent* aLight)
{
	mLights.push_back(aLight);
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

void Scene::DeregisterLight(LightComponent* aLight)
{
	std::vector<LightComponent*>::iterator foundLight = std::find(mLights.begin(), mLights.end(), aLight);

	if (foundLight != mLights.end())
	{
		mLights.erase(foundLight);
	}
}

void Scene::DeregisterCamera(CameraComponent* aCamera)
{
	std::vector<CameraComponent*>::iterator foundCamera = std::find(mCameras.begin(), mCameras.end(), aCamera);

	if (foundCamera != mCameras.end())
	{
		mCameras.erase(foundCamera);
	}
}