#include "MaterialComponent.h"
#include "../Material.h"
#include "../MaterialManager.h"
#include "ComponentTypes.h"
namespace BlueGengine
{
	MaterialComponent::MaterialComponent(Actor* aOwner) : ActorComponent(aOwner, EComponentType::EMaterialComponent)
	{
		mMaterial = MaterialManager::GI()->GetMaterial(0);
	}

	MaterialComponent::~MaterialComponent()
	{

	}

}

