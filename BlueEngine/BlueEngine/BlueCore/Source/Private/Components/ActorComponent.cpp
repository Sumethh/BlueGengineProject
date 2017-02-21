#include "Components/ActorComponent.h"
#include "Serialization/ArchiveObject.h"

ActorComponent::ActorComponent(Actor* aOwner) :
mEnabled(true),
		 mOwner(aOwner)
{

}

ActorComponent::~ActorComponent()
{

}

void ActorComponent::BeginPlay()
{

}

void ActorComponent::Update(float aDt)
{

}

void ActorComponent::LateUpdate(float aDt)
{

}

void ActorComponent::PreRender()
{

}

void ActorComponent::Render(IRenderer* aRenderer)
{

}

void ActorComponent::PostRender()
{

}

void ActorComponent::OnSerialize(ArchiveObject* const aArchiveObject) const
{
}

void ActorComponent::OnDeserialize(ArchiveObject* const aArchiveObject)
{
	EComponentType savedComponentType = (EComponentType)(aArchiveObject->Restore<uint32>("ComponentID"));
}

void ActorComponent::CalculateComponentBounds()
{
	mComponentBounds.position = glm::vec3(0, 0, 0);
	mComponentBounds.halfExtents = glm::vec3(0, 0, 0);
}

void ActorComponent::OnGizmoRender(GizmoRenderer* aRenderer)
{

}
