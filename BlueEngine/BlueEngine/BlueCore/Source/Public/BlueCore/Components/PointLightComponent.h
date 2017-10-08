#pragma once
#include "ILightComponent.h"

#include "BlueCore/Graphics/Light.h"

namespace Blue
{
	class PointLightComponent : public ILightComponent
	{
	public:
		DEFINE_ACTOR_COMPONENT_BASE_FUNCTIONALITY();

		PointLightComponent(Actor* aOwningActor);

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