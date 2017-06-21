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
	ComponentRegistery::ComponentRegistery()
	{
	}

	ComponentRegistery::~ComponentRegistery()
	{

	}

	void ComponentRegistery::Init()
	{
		RegisterComponentTypeInternal(MaterialComponent);
		RegisterComponentTypeInternal(DynamicMeshComponent).
		AddRequiredComponent(ActorComponent::ID<MaterialComponent>());

		RegisterComponentTypeInternal(CameraComponent);
		RegisterComponentTypeInternal(FirstPersonComponent);
	}

	ComponentRegistery* ComponentRegistery::mInstance = nullptr;
}