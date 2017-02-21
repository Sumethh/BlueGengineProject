#include "Components/ComponentRegistery.h"
#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/DynamicMeshComponent.h"
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
	Timer t;
	RegisterComponentTypeInternal(TransformComponent);
	RegisterComponentTypeInternal(MaterialComponent);
	RegisterComponentTypeInternal(DynamicMeshComponent).
	AddRequiredComponent(ActorComponent::ID<MaterialComponent>());
	auto elapsed = t.IntervalMCS();
}

ComponentRegistery* ComponentRegistery::mInstance = nullptr;
