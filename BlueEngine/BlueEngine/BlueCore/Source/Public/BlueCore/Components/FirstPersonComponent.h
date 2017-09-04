#pragma once
#include "BlueCore/Core/Types.h"
#include "ActorComponent.h"
//Temporary Component;

namespace Blue
{
	class FirstPersonComponent : public ActorComponent
	{
	public:
		FirstPersonComponent(Actor* aOwner);

		uint64 ID()
		{
			return StaticHash("FirstPersonComponent");
		}

		virtual void BeginPlay() override;
		virtual void Update(float aDt) override;

	private:
		float mLookSpeed = 20.0f;
		float mMoveSpeed = 5.0f;
	};
}