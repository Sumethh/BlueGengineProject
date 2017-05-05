#include "Components/MaterialComponent.h"
#include "Graphics/Material.h"
#include "Managers/MaterialManager.h"
#include "Components/ComponentTypes.h"

MaterialComponent::MaterialComponent(Actor* aOwner) : ActorComponent(aOwner)
{
	mMaterial = MaterialManager::GI()->GetMaterial(0);
}

MaterialComponent::~MaterialComponent()
{

}

