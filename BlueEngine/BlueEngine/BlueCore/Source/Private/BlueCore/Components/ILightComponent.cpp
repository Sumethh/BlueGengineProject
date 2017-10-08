#include "BlueCore/Components/ILightComponent.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Core/World.h"
namespace Blue
{


	ILightComponent::ILightComponent(Actor* aGO) : ActorComponent(aGO)
	{
	}

	ILightComponent::~ILightComponent()
	{
	}

	void ILightComponent::PostConstruction()
	{
		static_cast<Scene*>(GetOwner()->GetWorld())->RegisterLight(this);
	}

	void ILightComponent::PreDestruction()
	{
		static_cast<Scene*>(GetOwner()->GetWorld())->DeregisterLight(this);
	}

}