#include "Actor.h"
#include "Components/ActorComponent.h"
#include "Components/ComponentFactory.h"
namespace BlueGengine
{

	Actor::Actor(World* a_world) :
	m_hasBeginPlayBeenCalled(0),
							 m_world(a_world)
	{
		m_components.push_back(ComponentFactory::CreateComponent(EComponentType::ETransformComponent, this));
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

	void Actor::OnConstruct(EComponentType* a_componentsToAdd, uint32 a_componentCount)
	{
		if (a_componentCount && a_componentsToAdd)
		{
			for (size_t i = 0; i < a_componentCount; i++)
			{
				ActorComponent* newComponent = ComponentFactory::CreateComponent(a_componentsToAdd[i], this);
				m_components.push_back(newComponent);
			}
		}
	}

	void Actor::BeginPlay()
	{
		for (auto comp : m_components)
		{
			comp->BeginPlay();
		}
	}

	void Actor::Update(float a_dt)
	{
		for (auto comp : m_components)
		{
			comp->Update(a_dt);
		}
	}

	void Actor::LateUpdate(float a_dt)
	{
		for (auto comp : m_components)
		{
			comp->LateUpdate(a_dt);
		}
	}

	void Actor::PreRender()
	{
		for (auto comp : m_components)
		{
			comp->PreRender();
		}
	}

	void Actor::Render(IRenderer* a_renderer)
	{
		for (auto comp : m_components)
		{
			comp->Render(a_renderer);
		}
	}

	void Actor::PostRender()
	{
		for (auto comp : m_components)
		{
			comp->PostRender();
		}

		for (auto comp : m_componentsToAdd)
		{
			if (m_hasBeginPlayBeenCalled)
			{
				comp->BeginPlay();
			}

			m_components.push_back(comp);
		}
	}

}