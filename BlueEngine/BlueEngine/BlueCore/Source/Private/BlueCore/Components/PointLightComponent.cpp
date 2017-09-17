#include "BlueCore/Components/PointLightComponent.h"

#include "BlueCore/Core/Scene.h"
#include "BlueCore/Core/Actor.h"

namespace Blue
{

	PointLightComponent::PointLightComponent(Actor* aOwningActor) : ILightComponent(aOwningActor)
	{

	}

	void PointLightComponent::LateUpdate(float aDt)
	{
		mPosition = GetOwner()->GetTransform().position;
	}

	void PointLightComponent::RegisterPointLight()
	{
		Scene* scene = reinterpret_cast<Scene*>(GetOwner()->GetWorld());

	}

	void PointLightComponent::DeregisterPointLight()
	{

	}

}