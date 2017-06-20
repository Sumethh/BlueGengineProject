#include "Components/ActorComponent.h"
#include "Serialization/ArchiveObject.h"
#include "Core/Actor.h"

namespace Blue
{
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

	void ActorComponent::OnSerialize(ArchiveObject* const aArchiveObject) const
	{
	}

	void ActorComponent::OnDeserialize(ArchiveObject* const aArchiveObject)
	{
		EComponentType savedComponentType = (EComponentType)(aArchiveObject->Restore<uint32>("ComponentID"));
	}

	AABB ActorComponent::GetComponentBounds()
	{
		if (IsFlagSet(EActorComponentFlags::ComponentBoundsDirty))
		{
			CalculateComponentBounds();
		}

		return mComponentBounds;
	}

	void ActorComponent::CalculateComponentBounds()
	{
		mComponentBounds.position = glm::vec3(0, 0, 0);
		mComponentBounds.halfExtents = glm::vec3(0, 0, 0);
	}

	void ActorComponent::SetComponentFlags(EActorComponentFlags aFlags)
	{
		mFlags |= (uint32)aFlags;
	}

	void ActorComponent::ResetFlags(EActorComponentFlags aFlags)
	{
		mFlags &= ~(uint32)aFlags;

	}

	bool ActorComponent::IsFlagSet(EActorComponentFlags aFlags)
	{
		return (mFlags & (uint32)aFlags) > 0;
	}

	void ActorComponent::SetBoundsFlagDirty()
	{
		SetComponentFlags(EActorComponentFlags::ComponentBoundsDirty);
		GetOwner()->SetActorFlags(EActorFlags::ActorBoundsDirty);
	}
}