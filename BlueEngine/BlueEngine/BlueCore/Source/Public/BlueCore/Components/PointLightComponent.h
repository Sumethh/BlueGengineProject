#pragma once
#include "ILightComponent.h"

#include "BlueCore/Graphics/Light.h"

namespace Blue
{
	class PointLightComponent : public ILightComponent
	{
	public:
		PointLightComponent(Actor* aOwningActor);

		uint64 ID()override
		{
			return StaticHash("PointLightComponent");
		}

		inline glm::vec3 GetColor()
		{
			return mColor;
		}
		inline glm::vec3 GetLightPosition()
		{
			return mPosition;
		}

		inline void SetColor(glm::vec3 aColor)
		{
			mColor = aColor;
		}

		void LateUpdate(float aDt) override;

	private:
		void RegisterPointLight();
		void DeregisterPointLight();

		glm::vec3 mColor;
		glm::vec3 mPosition;
		uint32 mLightIndex;
	};
}