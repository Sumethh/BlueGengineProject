#include "World.h."
#include "Log.h"
#include "Actor.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Helpers/MathHelpers.h"
#include "Input.h"
#include "GizmoRenderer.h"
#include "imgui/imgui.h"
namespace BlueGengine
{
	Actor* cube = nullptr;
	World::World()
	{
		Log::LogInfo("World Constructed");
	}

	World::~World()
	{
		Log::LogInfo("World Destructed");
	}
	void World::BeginPlay()
	{
		Log::LogInfo("World BeginPlay");
		Actor* prevActor = nullptr;

		Actor* actor = nullptr;

		for (int i = 0; i < 200; i++)
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
			mActors.push_back(actor);

			if (prevActor)
			{
				actor->GetTransformComponent()->SetParent(prevActor->GetTransformComponent());
			}

			prevActor = actor;

		}

		actor = new BlueGengine::Actor(this);
		EComponentType playerComps[2] = { EComponentType::ECameraComponent, EComponentType::EFirstPersonComponent };
		actor->OnConstruct(playerComps, _countof(playerComps));
		mActors.push_back(actor);
		Transform transform = actor->GetTransformComponent()->GetTransform();
		transform.position = glm::vec3(0, 0, -10.0f);
		actor->GetTransformComponent()->SetTransform(transform);

		for (auto actor : mActors)
		{
			actor->BeginPlay();
		}
	}
	void World::Update(float aDt)
	{
		Transform t = cube->GetTransformComponent()->GetTransform();

		if (Input::GetKeyDown(Input::Key::Y))
		{
			t.rotation *= QuatFromEuler(glm::vec3(0, 10.0f * aDt, 0.0f));
		}
		else if (Input::GetKeyDown(Input::Key::T))
		{
			t.rotation *= QuatFromEuler(glm::vec3(0, -10.0f * aDt, 0.0));
		}

		ImGui::LabelText("rot", "%f %f %f %f", t.rotation.x, t.rotation.y, t.rotation.z, t.rotation.w);

		cube->GetTransformComponent()->SetTransform(t);

		for (auto actor : mActors)
		{
			actor->Update(aDt);
		}
	}

	void World::LateUpdate(float aDt)
	{
		for (auto actor : mActors)
		{
			actor->LateUpdate(aDt);
		}
	}

	void World::PreRender()
	{
		for (auto actor : mActors)
		{
			actor->PreRender();
		}
	}

	void World::Render(IRenderer* aRenderer)
	{
		for (auto actor : mActors)
		{
			actor->Render(aRenderer);
		}
	}

	void World::GizmoDraw(GizmoRenderer* aRenderer)
	{
		aRenderer->Begin(CameraComponent::GetActiveCamera());
		aRenderer->DrawCube(glm::vec3(0, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat(), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);
		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		aRenderer->Flush();
	}

	void World::PostRender()
	{

		for (auto actor : mActors)
		{
			actor->PostRender();
		}
	}

}