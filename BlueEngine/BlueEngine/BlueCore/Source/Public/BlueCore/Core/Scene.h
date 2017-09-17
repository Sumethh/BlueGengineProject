#pragma once
#include "Defines.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Core/Types.h"

#include <vector>


namespace Blue
{

	class Actor;
	class PrimitiveComponent;
	class CameraComponent;
	class ILightComponent;

	class Scene : public NonCopyable
	{
	public:
		Scene();
		~Scene();

		void RegisterPrimitiveComponent(PrimitiveComponent* aComponent);
		void RegisterLight(ILightComponent* aLight);
		void RegisterCamera(CameraComponent* aCamera);

		void DeregisterPimitiveComponent(PrimitiveComponent* aComponent);
		void DeregisterLight(ILightComponent* aLight);
		void DeregisterCamera(CameraComponent* aCamera);

		const std::vector<PrimitiveComponent*>& GetAllPrimitives()const
		{
			return mPrimitives;
		}

		const std::vector<CameraComponent*>& GetAllCameras()const
		{
			return mCameras;
		}

		const std::vector<ILightComponent*>& GetAllLights()const
		{
			return mLights;
		}

	private:

		std::vector<PrimitiveComponent*> mPrimitives;
		std::vector<ILightComponent*> mLights;
		std::vector<CameraComponent*> mCameras;
	};
}