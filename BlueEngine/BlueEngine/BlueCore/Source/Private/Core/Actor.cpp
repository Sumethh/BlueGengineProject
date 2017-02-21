#include "Core/Actor.h"

#include "Components/TransformComponent.h"
#include "Components/ActorComponent.h"

#include "Input/Input.h"
#include "Helpers/MathHelpers.h"
#include "Serialization/ArchiveObject.h"

#include <glm/glm.hpp>

Actor::Actor(World* a_world) :
mHasBeginPlayBeenCalled(0),
						mWorld(a_world)
{
	mTransform = AddComponent<TransformComponent>();
}

Actor::Actor(const Actor&)
{

}

Actor::Actor(Actor&&)
{

}

Actor::~Actor()
{

}

void Actor::OnConstruct()
{
	if ((mTransform = GetComponent<TransformComponent>()) == nullptr)
	{
		mTransform = AddComponent<TransformComponent>();
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
	ActorComponent* component = ActorComponent::Construct(aID, this);
	mComponentsToAdd.push_back(component);
	return component;
}

void Actor::AddRequiredComponents(uint64 aID)
{
	const std::vector<uint64>& requiredComps = ActorComponent::GetRequiredComponents(aID);

	for (int i = 0; i < requiredComps.size(); ++i)
	{
		if (!GetComponent(aID))
		{
			AddComponent(aID);
		}
	}
}
