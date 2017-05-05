#include "Components/ComponentRegistery.h"
#include "Core/Transformable.h"
#include "Components/MaterialComponent.h"
#include "Components/DynamicMeshComponent.h"
#include "Components/FirstPersonComponent.h"
#include "Components/CameraComponent.h"
#include "Core/Timer.h"
#define RegisterComponentTypeInternal(type) ComponentRegistery::GI()->RegisterComponent<##type>(CompileHash(#type))

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
