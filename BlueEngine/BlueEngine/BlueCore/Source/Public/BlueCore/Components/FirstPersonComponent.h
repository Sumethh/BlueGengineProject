#pragma once
#include "BlueCore/Core/Types.h"
#include "ActorComponent.h"
//Temporary Component;

namespace Blue
{
	class FirstPersonComponent : public ActorComponent
	{
	public:
		DEFINE_ACTOR_COMPONENT_BASE_FUNCTIONALITY();

		FirstPersonComponent(Actor* aOwner);

		virtual void BeginPlay() override;
		virtual void Update(float aDt) override;

	private:
		float mLookSpeed = 20.0f;
		float mMoveSpeed = 5.0f;
	};
}