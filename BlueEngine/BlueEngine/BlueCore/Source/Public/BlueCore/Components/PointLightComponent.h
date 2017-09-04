#pragma once
#include "ActorComponent.h"

#include "BlueCore/Graphics/Light.h"

namespace Blue
{
	class PointLightComponent : public ActorComponent
	{
	public:
		PointLightComponent(Actor* aOwningActor);

		uint64 ID()override
		{
			return StaticHash("PointLightComponent");
		}

		inline PointLight GetPointLight()
		{
			return mPointLight;
		}

		void LateUpdate(float aDt) override;

	private:
		void RegisterPointLight();
		void DeregisterPointLight();

		PointLight mPointLight;
		uint32 mLightIndex;
	};
}