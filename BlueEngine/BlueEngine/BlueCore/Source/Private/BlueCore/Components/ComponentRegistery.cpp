#include "BlueCore/Components/ComponentRegistery.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Components/MaterialComponent.h"
#include "BlueCore/Components/DynamicMeshComponent.h"
#include "BlueCore/Components/FirstPersonComponent.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Core/Timer.h"
#define RegisterComponentTypeInternal(type) Blue::ComponentRegistery::GI()->RegisterComponent<##type>(CompileHash(#type))

namespace Blue
{
	RegisteredComponentInfo& RegisteredComponentInfo::AddRequiredComponent(uint64 aHash)
	{
		requiredComponents.push_back(aHash);
		const std::vector<uint64>& componentReq = ComponentRegistery::GI()->GetComponentInfo(aHash).requiredComponents;

		for (const uint64& newHash : componentReq)
			AddRequiredComponent(newHash);

		return *this;
	}

	ComponentRegistery::ComponentRegistery()
	{
	}

	ComponentRegistery::~ComponentRegistery()
	{

	}

	void ComponentRegistery::Init()
	{
		size_t size = sizeof(MaterialComponent);
		size = sizeof(DynamicMeshComponent);
		size = sizeof(CameraComponent);
		size = sizeof(FirstPersonComponent);
		RegisterComponentTypeInternal(MaterialComponent);
		RegisterComponentTypeInternal(DynamicMeshComponent).
		AddRequiredComponent(ActorComponent::ID<MaterialComponent>());

		RegisterComponentTypeInternal(CameraComponent);
		RegisterComponentTypeInternal(FirstPersonComponent);
	}

	ComponentRegistery* ComponentRegistery::mInstance = nullptr;
}