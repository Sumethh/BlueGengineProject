#include "Core/World.h."
#include "Core/Log.h"
#include "Core/Actor.h"
#include "Core/Transformable.h"
#include "Components/CameraComponent.h"
#include "Helpers/MathHelpers.h"
#include "Input/Input.h"
#include "Renderers/GizmoRenderer.h"

#include "Collision/CollisionTests.h"
#include "Core/timer.h"
#include "Systems/StencilCreator.h"
#include "Serialization/Stencil/Stencil.h"
#include "Serialization/ArchiveObject.h"
#include "Serialization/Stencil/Stencil.h"
#include "Systems/Console.h"
#include "Managers/DebugManager.h"

namespace Blue
{
	World::World() : mHasBeginPlayBeenCalled(false)
	{
		Log::Info("World Constructed");
		Console::AddCommand("ReloadStencils", std::bind(&World::CommandReloadStencils, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}

	World::~World()
	{
		Log::Info("World Destructed");
	}
	void World::BeginPlay()
	{
		Log::Info("World BeginPlay");

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

	void World::GizmoDraw(GizmoRenderer* aRenderer)
	{
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

	Actor* World::CreateActor(Stencil* aStencil)
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

	Actor* World::CreateActor()
	{
		Actor* actor = new Actor(this);
		mActors.push_back(actor);
		return actor;
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
	}
}