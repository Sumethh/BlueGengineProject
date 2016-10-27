#include "World.h."
#include "Log.h"
#include "Actor.h"
#include "Components/TransformComponent.h"
#include "Helpers/MathHelpers.h"
#include "Input.h"
namespace BlueGengine
{
	Actor* cube;
	World::World()
	{
		LOGI("World Constructed");
	}

	World::~World()
	{
		LOGI("World Destructed");
	}
	void World::BeginPlay()
	{
		LOGI("World BeginPlay");
		Actor* prevActor = nullptr;

		Actor* actor = nullptr;
		for (int i = 0; i < 50; i++)
		{
			actor = new Actor(this);
			if (!cube)
			{
				cube = actor;
			}
			EComponentType comps[2] = { EComponentType::EMaterialComponent, EComponentType::EMeshComponent };
			actor->OnConstruct(comps, _countof(comps));
			auto t = actor->GetTransformComponent()->GetTransform();
			t.position = glm::vec3(2.0f * i, 0.0f, 0.0f);
			actor->GetTransformComponent()->SetTransform(t);
			m_actors.push_back(actor);

			if (prevActor)
			{
				actor->GetTransformComponent()->SetParent(prevActor->GetTransformComponent());
			}
			prevActor = actor;

		}
		actor = new BlueGengine::Actor(this);
		EComponentType playerComps[2] = { EComponentType::ECameraComponent, EComponentType::EFirstPersonComponent };
		actor->OnConstruct(playerComps, _countof(playerComps));
		m_actors.push_back(actor);
		Transform transform = actor->GetTransformComponent()->GetTransform();
		transform.position = glm::vec3(0, 0, -10.0f);
		actor->GetTransformComponent()->SetTransform(transform);
		for (auto actor : m_actors)
		{
			actor->BeginPlay();
		}
	}
	void World::Update(float a_dt)
	{
		Transform t = cube->GetTransformComponent()->GetTransform();

		if (Input::GetKeyDown(Input::Key::Y))
		{
			t.rotation *= QuatFromEuler(glm::vec3(0, 10.0f * a_dt, 0.0f));
		}
		else if (Input::GetKeyDown(Input::Key::T))
		{
			t.rotation *= QuatFromEuler(glm::vec3(0, -10.0f * a_dt, 0.0));
		}
		cube->GetTransformComponent()->SetTransform(t);

		for (auto actor : m_actors)
		{
			actor->Update(a_dt);
		}
	}

	void World::LateUpdate(float a_dt)
	{
		for (auto actor : m_actors)
		{
			actor->LateUpdate(a_dt);
		}
	}

	void World::PreRender()
	{
		for (auto actor : m_actors)
		{
			actor->PreRender();
		}
	}

	void World::Render(IRenderer* a_renderer)
	{
		for (auto actor : m_actors)
		{
			actor->Render(a_renderer);
		}
	}

	void World::PostRender()
	{

		for (auto actor : m_actors)
		{
			actor->PostRender();
		}
	}

}