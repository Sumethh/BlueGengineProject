#include "ActorComponent.h"
namespace BlueGengine
{

	ActorComponent::ActorComponent(Actor* a_owner, EComponentType a_compType) :
	m_enabled(true),
			  m_owner(a_owner),
			  m_componentType(a_compType)
	{

	}

	ActorComponent::~ActorComponent()
	{

	}

	void ActorComponent::BeginPlay()
	{

	}

	void ActorComponent::Update(float a_dt)
	{

	}

	void ActorComponent::LateUpdate(float a_dt)
	{

	}

	void ActorComponent::PreRender()
	{

	}

	void ActorComponent::Render(IRenderer* a_renderer)
	{

	}

	void ActorComponent::PostRender()
	{

	}
}