#include "BlueCore/Components/ILightComponent.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Core/World.h"
namespace Blue
{


	ILightComponent::ILightComponent(Actor* aGO) : ActorComponent(aGO)
	{
		static_cast<Scene*>(GetOwner()->GetWorld())->RegisterLight(this);
	}

	ILightComponent::~ILightComponent()
	{
		static_cast<Scene*>(GetOwner()->GetWorld())->DeregisterLight(this);
	}

}