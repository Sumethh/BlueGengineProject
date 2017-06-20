#pragma once
#include "ComponentTypes.h"
#include "../Serialization/ISerializable.h"
#include "../Collision/BoundingVolumes/AABB.h"
#include "ComponentRegistery.h"

namespace Blue
{
	class Actor;
	class IRenderer;
	class GizmoRenderer;

	enum class EActorComponentFlags : uint32
	{
		ComponentBoundsDirty = BlueBit(0)
	};

	class ActorComponent : public ISerializable
	{
	public:
		ActorComponent(Actor* aOwner);
		virtual ~ActorComponent();

		template <typename T>
		static T* Construct(Actor* aOwner)
		{
			static_assert(std::is_base_of<ActorComponent, T>(), "Type must inherit from Actor Component");
			return (T*)ComponentRegistery::GI()->Construct<T>(aOwner);
		}
		static ActorComponent* Construct(uint64 aID, Actor* aOwner)
		{
			return ComponentRegistery::GI()->Construct(aID, aOwner);
		}

		template <typename T>
		static const std::vector<uint64>& GetRequiredComponents()
		{
			return ComponentRegistery::GI()->GetComponentInfo<T>().requiredComponents;
		}

		static const std::vector<uint64>& GetRequiredComponents(uint64 aID)
		{
			return ComponentRegistery::GI()->GetComponentInfo(aID).requiredComponents;
		}

		virtual void BeginPlay();
		virtual void Update(float aDt);
		virtual void LateUpdate(float aDt);

		virtual void OnSerialize(ArchiveObject* const aArchiveObject) const override;
		virtual void OnDeserialize(ArchiveObject* const aArchiveObject) override;
		inline Actor* GetOwner()const
		{
			return mOwner;
		}

		inline bool Enabled()const
		{
			return mEnabled;
		}
		inline void SetEnabled(bool aNewEnabled)
		{
			mEnabled = aNewEnabled;
		}

		//Position is relative to the owning actor
		AABB GetComponentBounds();

		template<typename T>
		static uint64 ID()
		{
			return ComponentRegistery::GI()->GetComponentInfo<T>().componentHash;
		}
		virtual uint64 ID() = 0;

	protected:
		//Position is relative to the owning actor
		virtual void CalculateComponentBounds();

		AABB mComponentBounds;

		void SetComponentFlags(EActorComponentFlags aFlags);
		void ResetFlags(EActorComponentFlags aFlags);
		bool IsFlagSet(EActorComponentFlags aFlags);
	protected:
		void SetBoundsFlagDirty();

	private:

		bool mEnabled;
		uint64 mInstanceID;
		Actor* mOwner;
		uint32 mFlags;
	};
}