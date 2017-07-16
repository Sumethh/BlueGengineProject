#include "BlueCore/Core/World.h."
#include "BlueCore/Core/Log.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Renderers/GizmoRenderer.h"

#include "BlueCore/Collision/CollisionTests.h"
#include "BlueCore/Core/timer.h"
#include "BlueCore/Systems/StencilCreator.h"
#include "BlueCore/Serialization/Stencil/Stencil.h"
#include "BlueCore/Serialization/ArchiveObject.h"
#include "BlueCore/Serialization/Stencil/Stencil.h"
#include "BlueCore/Systems/Console.h"
#include "BlueCore/Managers/DebugManager.h"
#include "BlueCore/Managers/DebugManager.h";


namespace Blue
{
	World::World() : mHasBeginPlayBeenCalled(false)
	{
		Log::Info("World Constructed");
		Console::AddCommand("ReloadStencils", std::bind(&World::CommandReloadStencils, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		Log::Info(std::to_string(sizeof(Actor)));
		Log::Info(std::to_string(sizeof(glm::mat4)));
		Log::Info(std::to_string(sizeof(std::vector<int*>)));
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
		Actor* actor = mActorAllocator.AllocateActor(this);
		int32 index = actor->GetAllocationIndex();
		if (mActors.size() > index)
		{
			int32 replacingIndex = mActors[index]->GetAllocationIndex();
			assert(replacingIndex != index);
			if (replacingIndex > index)
			{
				std::vector<Actor*>::iterator location = mActors.begin() + index;
				mActors.insert(location, actor);
			}
			else
			{
				std::vector<Actor*>::iterator location = mActors.begin() + index + 1;
				mActors.insert(location, actor);
			}
		}
		else
			mActors.emplace_back(actor);
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