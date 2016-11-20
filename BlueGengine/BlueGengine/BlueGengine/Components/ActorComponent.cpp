#include "ActorComponent.h"
namespace BlueGengine
{

	ActorComponent::ActorComponent(Actor* aOwner, EComponentType aCompType) :
	mEnabled(true),
			 mOwner(aOwner),
			 mComponentType(aCompType)
	{

	}

	ActorComponent::~ActorComponent()
	{

	}

	void ActorComponent::BeginPlay()
	{

	}

	void ActorComponent::Update(float aDt)
	{

	}

	void ActorComponent::LateUpdate(float aDt)
	{

	}

	void ActorComponent::PreRender()
	{

	}

	void ActorComponent::Render(IRenderer* aRenderer)
	{

	}

	void ActorComponent::PostRender()
	{

	}

	void ActorComponent::OnGizmoRender(GizmoRenderer* aRenderer)
	{

	}

}