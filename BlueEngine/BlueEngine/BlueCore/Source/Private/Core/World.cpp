#include "Core/World.h."
#include "Core/Log.h"
#include "Core/Actor.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Helpers/MathHelpers.h"
#include "Input/Input.h"
#include "Renderers/GizmoRenderer.h"
#include "Imgui/imgui.h"
#include "Collision/CollisionTests.h"
#include "Core/timer.h"
#include "Systems/StencilCreator.h"
#include "Serialization/Stencil/Stencil.h"
#include "Serialization/ArchiveObject.h"
#include "Serialization/Stencil/Stencil.h"
#include "Systems/Console.h"
#include "Managers/DebugManager.h"
namespace BlueCore
{
	Actor* cube = nullptr;
	Actor* cube2 = nullptr;
	World::World() : mHasBeginPlayBeenCalled(false)
	{
		Log::LogInfo("World Constructed");
		mStencilManager.Init();
		Console::AddCommand("ReloadStencils", std::bind(&World::CommandReloadStencils, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		Console::AddCommand("SpawnActorFromStencil", std::bind(&World::CommandSpawnActorFromStencil, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
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

		for (int i = 0; i < 2; i++)
		{
			actor = new Actor(this);

			if (!cube)
			{
				cube = actor;
			}

			EComponentType comps[2] = { EComponentType::EMaterialComponent, EComponentType::EMeshComponent };
			actor->OnConstruct(comps, _countof(comps));
			auto t = actor->GetTransformComponent()->GetTransform();
			t.position = glm::vec3(1.0f * i, 0.0f, 0.0f);
			actor->GetTransformComponent()->SetTransform(t);
			mActors.push_back(actor);

			prevActor = actor;

		}

		cube2 = mActors[1];
		actor = new BlueCore::Actor(this);
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

		mHasBeginPlayBeenCalled = true;
	}
	void World::Update(float aDt)
	{
		StencilCreator::GI()->Update();


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
		aRenderer->DrawPlane(glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat(), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);
		aRenderer->DrawCapsule(glm::vec3(4.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat(), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);
		aRenderer->DrawSphere(glm::vec3(6.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);

		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -10.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		aRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		aRenderer->Flush();
	}

	void World::PostRender()
	{

		for (auto actor : mActors)
		{
			actor->PostRender();
		}
	}

	BlueCore::Actor* World::CreateActor(Stencil* aStencil)
	{
		Actor* newActor = new Actor(this);
		aStencil->Stamp(newActor);

		if (mHasBeginPlayBeenCalled)
		{
			newActor->BeginPlay();
		}

		mActors.push_back(newActor);
		return newActor;
	}

	void World::Save(ArchiveObject& aArchiveObject)
	{
		ArchiveObject actors("Actors");

		for (uint32 i = 0; i < mActors.size(); ++i)
		{
			ArchiveObject actor(std::to_string(i));
			mActors[i]->OnSerialize(&actor);
			actors.Archive(&actor);
		}

		aArchiveObject.Archive(&actors);
	}

	void World::CommandReloadStencils(std::string aCommand, std::string* aArg, uint32 aArgCount)
	{
		mStencilManager.Init();
	}

	void World::CommandSpawnActorFromStencil(std::string aCommand, std::string* aArg, uint32 aArgCount)
	{
		if (aArgCount != 4)
		{
			Log::LogInfo("Spawn Actor from stencil takes 4 arguments, StencilName, PosX PosY PosZ");
			return;
		}

		Stencil* sten = mStencilManager.GetStencil(aArg[0]);

		if (!sten)
		{
			Log::LogInfo("Could not find Stencil: " + aArg[0]);
			return;
		}

		glm::vec3 newPos;
		newPos.x = std::stof(aArg[1]);
		newPos.y = std::stof(aArg[2]);
		newPos.z = std::stof(aArg[3]);

		Actor* actor = CreateActor(sten);

		Transform t = actor->GetTransformComponent()->GetTransform();
		t.position = newPos;
		actor->GetTransformComponent()->SetTransform(t);

	}

}