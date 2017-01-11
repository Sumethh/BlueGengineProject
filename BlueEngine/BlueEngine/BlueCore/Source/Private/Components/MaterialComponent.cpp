#include "Components/MaterialComponent.h"
#include "Graphics/Material.h"
#include "Managers/MaterialManager.h"
#include "Components/ComponentTypes.h"
namespace BlueCore
{
	MaterialComponent::MaterialComponent(Actor* aOwner) : ActorComponent(aOwner, EComponentType::EMaterialComponent)
	{
		mMaterial = MaterialManager::GI()->GetMaterial(0);
	}

	MaterialComponent::~MaterialComponent()
	{

	}

}

