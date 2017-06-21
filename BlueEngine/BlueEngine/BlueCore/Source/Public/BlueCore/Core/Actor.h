#pragma once
#include "BlueCore/Components/ActorComponent.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Serialization/ISerializable.h"
#include "BlueCore/Collision/BoundingVolumes/AABB.h"

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
		~Actor();

		void OnConstruct();
		void BeginPlay();
		void Update(float aDt);
		void LateUpdate(float aDt);

		void OnSerialize(ArchiveObject* const aArchiveObject) const override;
		void OnDeserialize(ArchiveObject* const aArchiveObject) override;
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

		const uint32 GetAllocationIndex()
		{
			return mAllocationIndex;
		}
	private:

		void AddRequiredComponents(uint64 aID);
		void RecalculateActorBounds();

		bool mHasBeginPlayBeenCalled;
		World* mWorld;

		uint64 mInstanceID;
		uint32 mAllocationIndex;
		AABB mActorBounds;

		std::vector<ActorComponent*> mComponents;
		std::vector<ActorComponent*> mComponentsToAdd;

		uint32 mActorFlags;

		friend class ActorAllocator;
		void SetAllocationIndex(uint32 aNewIndex)
		{
			mAllocationIndex = aNewIndex;
		}
	};
}