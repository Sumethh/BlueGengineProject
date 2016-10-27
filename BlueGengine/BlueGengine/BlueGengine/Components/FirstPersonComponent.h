#pragma once
#include "../Types.h"
#include "ActorComponent.h"
//Temporary Component;
namespace BlueGengine
{
	class FirstPersonComponent : public ActorComponent
	{
		public:
		FirstPersonComponent(Actor* a_owner);

		virtual void Update(float a_dt) override;

		private:
		float m_lookSpeed = 100.0f;
		float m_moveSpeed = 5.0f;
		float r = 0.0f;
	};
}