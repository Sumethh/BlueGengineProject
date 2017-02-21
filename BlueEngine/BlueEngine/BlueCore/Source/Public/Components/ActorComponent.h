#pragma once
#include "ComponentTypes.h"
#include "../Serialization/ISerializable.h"
#include "../Collision/BoundingVolumes/AABB.h"
#include "ComponentRegistery.h"

class Actor;
class IRenderer;
class GizmoRenderer;
class   ActorComponent: public ISerializable
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
	virtual void PreRender();
	virtual void Render(IRenderer* aRenderer);
	virtual void OnGizmoRender(GizmoRenderer* aRenderer);
	virtual void PostRender();

	virtual void OnSerialize(ArchiveObject* const aArchiveObject) const override;
	virtual void OnDeserialize(ArchiveObject* const aArchiveObject) override;
	inline Actor* GetOwner()const { return mOwner; }

	inline bool Enabled()const { return mEnabled; }
	inline void SetEnabled(bool aNewEnabled) { mEnabled = aNewEnabled; }

	AABB GetComponentBounds() const {return mComponentBounds;};

	template<typename T>
	static uint64 ID() { return ComponentRegistery::GI()->GetComponentInfo<T>().componentHash; }
	virtual uint64 ID() = 0;
	protected:
	virtual void CalculateComponentBounds();
	void SetActorBounds(AABB aNewBounds) { mComponentBounds = aNewBounds; }
	AABB mComponentBounds;

	private:

	bool mEnabled;
	uint64 mInstanceID;
	Actor* mOwner;
};
