#pragma once
#include "Defines.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Core/Types.h"

#include <vector>


namespace Blue
{
	class Actor;
	class PrimitiveComponent;
	class PointLight;
	class CameraComponent;
	class Scene : public NonCopyable
	{
	public:
		Scene();
		~Scene();

		void RegisterPrimitiveComponent(PrimitiveComponent* aComponent);
		void RegisterPointLight(PointLight* aLight);
		void RegisterCamera(CameraComponent* aCamera);

		void DeregisterPimitiveComponent(PrimitiveComponent* aComponent);
		void DeregisterLight(uint32 aLightIndex);
		void DeregisterCamera(CameraComponent* aCamera);

		const std::vector<PrimitiveComponent*>& GetAllPrimitives()const
		{
			return mPrimitives;
		}
		const std::vector<LightComponent*>& GetAllLights()const
		{
			return mLights;
		}
		const std::vector<CameraComponent*>& GetAllCameras()const
		{
			return mCameras;
		}

	private:

		std::vector<PrimitiveComponent*> mPrimitives;
		std::vector<LightComponent*> mLights;
		std::vector<CameraComponent*> mCameras;

	};
}