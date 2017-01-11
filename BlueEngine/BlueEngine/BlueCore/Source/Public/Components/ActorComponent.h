#pragma once
#include "ComponentTypes.h"
#include "../Serialization/ISerializable.h"
#include "../Collision/BoundingVolumes/AABB.h"
namespace BlueCore
{
	class Actor;
	class IRenderer;
	class GizmoRenderer;
	class ActorComponent : public ISerializable
	{
		public:
		ActorComponent(Actor* aOwner, EComponentType aCompType);
		virtual ~ActorComponent();

		virtual void BeginPlay();
		virtual void Update(float aDt);
		virtual void LateUpdate(float aDt);
		virtual void PreRender();
		virtual void Render(IRenderer* aRenderer);
		virtual void OnGizmoRender(GizmoRenderer* aRenderer);
		virtual void PostRender();

		virtual void OnSerialize(ArchiveObject* const aArchiveObject) const override;
		virtual void OnDeserialize(ArchiveObject* const aArchiveObject) override;
		inline Actor* GetOwner()const { return mOwner; }

		inline bool Enabled()const { return mEnabled; }
		inline bool SetEnabled(bool aNewEnabled) { mEnabled = aNewEnabled; }


		AABB GetComponentBounds() const {return mComponentBounds;};

		inline EComponentType GetComponentType()const { return mComponentType; }
		protected:
		virtual void CalculateComponentBounds();
		void SetActorBounds(AABB aNewBounds) { mComponentBounds = aNewBounds; }
		AABB mComponentBounds;

		private:

		bool mEnabled;
		EComponentType mComponentType;
		uint64 mInstanceID;
		Actor* mOwner;
	};
}