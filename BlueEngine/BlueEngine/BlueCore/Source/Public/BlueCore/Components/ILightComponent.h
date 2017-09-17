#pragma once
#include "BlueCore/BlueCore.h"
#include "BlueCore/Graphics/Light.h"
#include "BlueCore/Components/ActorComponent.h"



namespace Blue
{
	class ILightComponent : public ActorComponent
	{
	public:
		ILightComponent(Actor* aGO);
		~ILightComponent();

		inline ELightType GetLightType()
		{
			return mLightType;
		}

	private:
		ELightType mLightType;
	};
}
