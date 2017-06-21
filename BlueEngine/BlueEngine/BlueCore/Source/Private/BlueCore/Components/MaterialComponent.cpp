#include "BlueCore/Components/MaterialComponent.h"
#include "BlueCore/Graphics/Material.h"
#include "BlueCore/Managers/MaterialManager.h"
#include "BlueCore/Components/ComponentTypes.h"

namespace Blue
{
	MaterialComponent::MaterialComponent(Actor* aOwner) : ActorComponent(aOwner)
	{
		mMaterial = MaterialManager::GI()->GetMaterial(0);
	}

	MaterialComponent::~MaterialComponent()
	{
		mMaterial = nullptr;
	}
}