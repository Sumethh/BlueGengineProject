#include "BlueCore/Core/Actor.h"
#include "BlueCore/Components/ActorComponent.h"

#include "BlueCore/Input/Input.h"
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Serialization/ArchiveObject.h"

#include <glm/glm.hpp>

namespace Blue
{

	Actor::Actor(World* a_world) :
		mHasBeginPlayBeenCalled(0),
		mWorld(a_world)
	{
	}

	Actor::Actor(const Actor&)
	{

	}

	Actor::Actor(Actor&&)
	{

	}

	Actor::~Actor()
	{
		for (ActorComponent* comp : mComponents)
		{
			comp->~ActorComponent();
		}
	}

	void Actor::OnConstruct()
	{
		for (ActorComponent* component : mComponentsToAdd)
		{
			mComponents.emplace_back(component);
		}
	}

	void Actor::BeginPlay()
	{
		for (auto component = mComponentsToAdd.begin(); component != mComponentsToAdd.end();)
		{
			mComponents.push_back(*component);
			component = mComponentsToAdd.erase(component);
		}

		for (auto comp : mComponents)
		{
			comp->BeginPlay();
		}

		mHasBeginPlayBeenCalled = true;
	}

	void Actor::Update(float aDt)
	{
		for (auto comp = mComponentsToAdd.begin(); comp != mComponentsToAdd.end();)
		{
			if (mHasBeginPlayBeenCalled)
			{
				(*comp)->BeginPlay();
			}

			mComponents.push_back(*comp);
			comp = mComponentsToAdd.erase(comp);
		}

		for (auto comp : mComponents)
		{
			comp->Update(aDt);
		}
	}

	void Actor::LateUpdate(float aDt)
	{
		for (auto comp : mComponents)
		{
			comp->LateUpdate(aDt);
		}

		if (IsFlagSet(EActorFlags::ActorBoundsDirty))
		{
			RecalculateActorBounds();
			ResetFlags(EActorFlags::ActorBoundsDirty);
		}
	}

	void Actor::OnSerialize(ArchiveObject* const aArchiveObject) const
	{
		ArchiveObject components("Components");

		for (uint32 i = 0; i < mComponents.size(); ++i)
		{
			ArchiveObject component(std::to_string(i));
			mComponents[i]->OnSerialize(&component);
			components.Archive(&component);
		}

		aArchiveObject->Archive(&components);
	}

	void Actor::OnDeserialize(ArchiveObject* const aArchiveObject)
	{

	}

	ActorComponent* Actor::GetComponent(uint64 aID)
	{
		for (ActorComponent* component : mComponents)
		{
			if (component->ID() == aID)
			{
				return component;
			}
		}

		for (ActorComponent* component : mComponentsToAdd)
		{
			if (component->ID() == aID)
			{
				return component;
			}
		}

		return nullptr;
	}

	std::vector<ActorComponent*> Actor::GetAllComponents(uint64 aID)
	{
		std::vector<ActorComponent*> components;

		for (ActorComponent* component : mComponents)
		{
			if (component->ID() == aID)
			{
				components.push_back(component);
			}
		}

		for (ActorComponent* component : mComponentsToAdd)
		{
			if (component->ID() == aID)
			{
				components.push_back(component);
			}
		}

		return components;
	}

	ActorComponent* Actor::AddComponent(uint64 aID)
	{
		const std::vector<uint64>& requiredComponents = ActorComponent::GetRequiredComponents(aID);
		ComponentRegistery* componentRegistery = ComponentRegistery::GI();

		for (const uint64& compHash : requiredComponents)
		{
			AddComponent(compHash);
		}

		ActorComponent* component = ActorComponent::Construct(aID, this);
		component->PostConstruction();
		mComponentsToAdd.push_back(component);
		return component;
	}

	AABB Actor::GetActorBounds()
	{
		if (IsFlagSet(EActorFlags::ActorBoundsDirty))
		{
			RecalculateActorBounds();
		}

		return mActorBounds;
	}

	void Actor::SetActorFlags(EActorFlags aFlag)
	{
		mActorFlags |= (uint32)aFlag;
	}

	void Actor::ResetFlags(EActorFlags aFlags)
	{
		mActorFlags &= ~(uint32)aFlags;
	}

	bool Actor::IsFlagSet(EActorFlags aFlags)
	{
		return (mActorFlags & (uint32)aFlags) != 0;
	}

	void Actor::AddRequiredComponents(uint64 aID)
	{
		const std::vector<uint64>& requiredComps = ActorComponent::GetRequiredComponents(aID);

		for (int i = 0; i < requiredComps.size(); ++i)
		{
			if (!GetComponent(requiredComps[i]))
			{
				AddComponent(requiredComps[i]);
			}
		}
	}

	void Actor::RecalculateActorBounds()
	{
		glm::vec3 maxPositions(std::numeric_limits<float>::min());
		glm::vec3 minPositions(std::numeric_limits<float>::max());

		for (sizeInt i = 0; i < mComponents.size(); ++i)
		{
			AABB componentBox = mComponents[i]->GetComponentBounds();

			if (componentBox.IsZeroSized())
			{
				continue;
			}

			glm::vec3 maxComponentPositions = componentBox.position + componentBox.halfExtents;
			glm::vec3 minComponentPositions = componentBox.position - componentBox.halfExtents;

			maxPositions.x = glm::max(maxPositions.x, maxComponentPositions.x);
			maxPositions.y = glm::max(maxPositions.y, maxComponentPositions.y);
			maxPositions.z = glm::max(maxPositions.z, maxComponentPositions.z);

			minPositions.x = glm::min(minPositions.x, minComponentPositions.x);
			minPositions.y = glm::min(minPositions.y, minComponentPositions.y);
			minPositions.z = glm::min(minPositions.z, minComponentPositions.z);
		}

		mActorBounds.halfExtents = (maxPositions - minPositions) / 2.0f;
		mActorBounds.position = minPositions + mActorBounds.halfExtents + GetTransform().position;
	}
}