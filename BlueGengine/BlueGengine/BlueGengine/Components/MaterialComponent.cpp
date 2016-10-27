#include "MaterialComponent.h"
#include "../Material.h"
#include "../MaterialManager.h"
#include "ComponentTypes.h"
namespace BlueGengine
{
	MaterialComponent::MaterialComponent(Actor* a_owner) : ActorComponent(a_owner, EComponentType::EMaterialComponent)
	{
		m_material = MaterialManager::GI()->GetMaterial(0);
	}

	MaterialComponent::~MaterialComponent()
	{

	}

}

