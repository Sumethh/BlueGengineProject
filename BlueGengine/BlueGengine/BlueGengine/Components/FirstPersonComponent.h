#pragma once
#include "../Types.h"
#include "ActorComponent.h"
//Temporary Component;
namespace BlueGengine
{
	class FirstPersonComponent : public ActorComponent
	{
		public:
		FirstPersonComponent(Actor* aOwner);

		virtual void BeginPlay() override;
		virtual void Update(float aDt) override;

		private:
		float mLookSpeed = 20.0f;
		float mMoveSpeed = 5.0f;
	};
}