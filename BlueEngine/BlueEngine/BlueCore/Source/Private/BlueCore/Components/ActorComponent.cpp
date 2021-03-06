#include "BlueCore/Components/ActorComponent.h"
#include "BlueCore/Serialization/ArchiveObject.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Managers/MemoryManager.h"

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

	void ActorComponent::PostConstruction()
	{

	}

	void ActorComponent::PreDestruction()
	{

	}

	void ActorComponent::BeginPlay()
	{

	}

	void ActorComponent::Update(float aDt)
	{
		(float)aDt;
	}

	void ActorComponent::LateUpdate(float aDt)
	{
		(void)aDt;
	}

	void ActorComponent::OnSerialize(ArchiveObject* const aArchiveObject) const
	{
		(void)aArchiveObject;
	}

	void ActorComponent::OnDeserialize(ArchiveObject* const aArchiveObject)
	{
		(void)aArchiveObject;
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