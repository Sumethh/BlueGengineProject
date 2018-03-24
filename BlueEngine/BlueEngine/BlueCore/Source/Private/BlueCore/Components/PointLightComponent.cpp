#include "BlueCore/Components/PointLightComponent.h"

#include "BlueCore/Core/Scene.h"
#include "BlueCore/Core/Actor.h"

namespace Blue
{
	IMPLEMENT_ACTOR_COMPONENT_BASE_FUNCTIONALITY(PointLightComponent);

	PointLightComponent::PointLightComponent(Actor* aOwningActor) : ILightComponent(aOwningActor)
	{

	}

	void PointLightComponent::LateUpdate(float aDt)
	{
		(void)aDt;
		mPosition = GetOwner()->GetTransform().position;
	}

	void PointLightComponent::RegisterPointLight()
	{		

	}

	void PointLightComponent::DeregisterPointLight()
	{

	}

}