#pragma once
#include "Components/ActorComponent.h"
#include <vector>
#include "Serialization/ISerializable.h"
class World;
class ActorComponent;
class IRenderer;
class TransformComponent;
class GizmoRenderer;

class   Actor : public ISerializable
{
	public:
	Actor(World* a_world);
	Actor(const Actor&);
	Actor(Actor&&);
	virtual ~Actor();

	virtual void OnConstruct();
	virtual void BeginPlay();
	virtual void Update(float aDt);
	virtual void LateUpdate(float aDt);

	virtual void OnSerialize(ArchiveObject* const aArchiveObject) const override;
	virtual void OnDeserialize(ArchiveObject* const aArchiveObject);

	inline TransformComponent* GetTransformComponent() { return mTransform; }
	inline World* GetWorld() { return mWorld; }

	ActorComponent* GetComponent(uint64 aID);
	std::vector<ActorComponent*> GetAllComponents(uint64 aID);
	ActorComponent* AddComponent(uint64 aID);

	template<typename T>
	T* GetComponent()
	{
		return (T*)GetComponent(ActorComponent::ID<T>());
	}

	template<typename T>
	T* AddComponent()
	{
		return (T*)AddComponent(ActorComponent::ID<T>());
	}

	private:

	void AddRequiredComponents(uint64 aID);

	TransformComponent* mTransform;

	bool mHasBeginPlayBeenCalled;
	World* mWorld;
	uint64 mInstanceID;

	std::vector<ActorComponent*> mComponents;
	std::vector<ActorComponent*> mComponentsToAdd;
};
