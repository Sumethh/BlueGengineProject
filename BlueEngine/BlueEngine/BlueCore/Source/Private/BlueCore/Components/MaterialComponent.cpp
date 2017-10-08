#include "BlueCore/Components/MaterialComponent.h"
#include "BlueCore/Graphics/Material.h"
#include "BlueCore/Managers/MaterialManager.h"
#include "BlueCore/Components/ComponentTypes.h"

namespace Blue
{
	IMPLEMENT_ACTOR_COMPONENT_BASE_FUNCTIONALITY(MaterialComponent);

	MaterialComponent::MaterialComponent(Actor* aOwner) : ActorComponent(aOwner)
	{
	}

	MaterialComponent::~MaterialComponent()
	{
		mMaterial = nullptr;
	}

	void MaterialComponent::PostConstruction()
	{
		mMaterial = MaterialManager::GI()->GetMaterial(0);
	}

}