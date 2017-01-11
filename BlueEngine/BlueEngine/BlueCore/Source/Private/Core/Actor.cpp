#include "Core/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/ComponentFactory.h"
#include "Input/Input.h"
#include <glm/glm.hpp>
#include "Helpers/MathHelpers.h"
#include "Serialization/ArchiveObject.h"
namespace BlueCore
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

	}

	void Actor::OnConstruct(EComponentType* aComponentsToAdd, uint32 aComponentCount)
	{
		if (aComponentCount && aComponentsToAdd)
		{
			for (size_t i = 0; i < aComponentCount; i++)
			{
				ActorComponent* newComponent = ComponentFactory::CreateComponent(aComponentsToAdd[i], this);
				mComponents.push_back(newComponent);
			}
		}

		if ((mTransform = (TransformComponent*)GetComponent(EComponentType::ETransformComponent)) == nullptr)
		{
			mTransform = (TransformComponent*)ComponentFactory::CreateComponent(EComponentType::ETransformComponent, this);
			mComponents.push_back((ActorComponent*)mTransform);
		}

	}

	void Actor::BeginPlay()
	{
		for (auto comp : mComponents)
		{
			comp->BeginPlay();
		}

		mHasBeginPlayBeenCalled = true;
	}

	void Actor::Update(float aDt)
	{
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

	void Actor::PreRender()
	{
		for (auto comp : mComponents)
		{
			comp->PreRender();
		}
	}

	void Actor::Render(IRenderer* aRenderer)
	{
		for (auto comp : mComponents)
		{
			comp->Render(aRenderer);
		}
	}

	void Actor::PostRender()
	{
		for (auto comp : mComponents)
		{
			comp->PostRender();
		}

		for (auto comp = mComponentsToAdd.begin(); comp != mComponentsToAdd.end();)
		{
			if (mHasBeginPlayBeenCalled)
			{
				(*comp)->BeginPlay();
			}

			mComponents.push_back(*comp);
			comp = mComponentsToAdd.erase(comp);
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

	void Actor::OnDrawGizmo(GizmoRenderer* aRenderer)
	{

	}

	ActorComponent* Actor::GetComponent(EComponentType aComponentType)
	{
		for (auto comp : mComponents)
		{
			if (comp->GetComponentType() == aComponentType)
			{
				return comp;
			}
		}

		return nullptr;
	}

	BlueCore::ActorComponent* Actor::AddComponent(EComponentType aComponentType)
	{
		ActorComponent* comp = ComponentFactory::CreateComponent(aComponentType, this);

		if (!mHasBeginPlayBeenCalled)
		{
			mComponents.push_back(comp);
		}
		else
		{
			mComponentsToAdd.push_back(comp);
		}

		return comp;

	}

}