#pragma once
#include "Components/ActorComponent.h"
#include "Core/Transformable.h"
#include "Serialization/ISerializable.h"
#include "Collision\BoundingVolumes\AABB.h"

#include <vector>

namespace Blue
{
	class World;
	class ActorComponent;
	class IRenderer;
	class Transformable;
	class GizmoRenderer;

	enum class EActorFlags : uint32
	{
		ActorBoundsDirty = BlueBit(0),
	};

	class Actor : public Transformable
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
		inline World* GetWorld()
		{
			return mWorld;
		}

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

		AABB GetActorBounds();

		void SetActorFlags(EActorFlags aFlags);
		void ResetFlags(EActorFlags aFlags);
		bool IsFlagSet(EActorFlags aFlags);

	private:

		void AddRequiredComponents(uint64 aID);
		void RecalculateActorBounds();

		bool mHasBeginPlayBeenCalled;
		World* mWorld;

		uint64 mInstanceID;
		AABB mActorBounds;

		std::vector<ActorComponent*> mComponents;
		std::vector<ActorComponent*> mComponentsToAdd;

		uint32 mActorFlags;
	};
}