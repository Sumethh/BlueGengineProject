#pragma once
#include "Components/ComponentTypes.h"
#include <vector>
#include "Serialization/ISerializable.h"
namespace BlueCore
{
	class World;
	class ActorComponent;
	class IRenderer;
	class TransformComponent;
	class GizmoRenderer;
	class Actor : public ISerializable
	{
		public:
		Actor(World* a_world);
		Actor(const Actor&);
		Actor(Actor&&);
		virtual ~Actor();

		virtual void OnConstruct(EComponentType* aComponentsToAdd, uint32 aComponentCount = 0);
		virtual void BeginPlay();
		virtual void Update(float aDt);
		virtual void LateUpdate(float aDt);
		virtual void PreRender();
		virtual void Render(IRenderer* aRenderer);
		virtual void OnDrawGizmo(GizmoRenderer* aRenderer);
		virtual void PostRender();

		virtual void OnSerialize(ArchiveObject* const aArchiveObject) const override;
		virtual void OnDeserialize(ArchiveObject* const aArchiveObject);

		inline TransformComponent* GetTransformComponent() { return mTransform; }

		ActorComponent* GetComponent(EComponentType aComponentType);
		ActorComponent* AddComponent(EComponentType aComponentType);

		inline World* GetWorld() { return mWorld; }



		private:
		TransformComponent* mTransform;

		bool mHasBeginPlayBeenCalled;
		World* mWorld;
		uint64 mInstanceID;

		std::vector<ActorComponent*> mComponents;
		std::vector<ActorComponent*> mComponentsToAdd;
	};

}