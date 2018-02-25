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

#include "BlueCore/Graphics/Mesh.h"


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

	Vertex verts[] = { {glm::vec3(0, 0, 0)}, {glm::vec3(0, 0, -10)}, {glm::vec3(-10, 0, 0)} };
	uint32 indicies[] = { 0, 1, 2 };

	Mesh TestMesh(123123);

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
		/*
		mGizmoRenderer->DrawMesh(&TestMesh, glm::vec3(1, 0, 0));
		mGizmoRenderer->DrawCube(glm::vec3(0, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat(), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);
		mGizmoRenderer->DrawPlane(glm::vec3(2.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat(), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);
		mGizmoRenderer->DrawCapsule(glm::vec3(4.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::quat(), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);
		mGizmoRenderer->DrawSphere(glm::vec3(6.0f, 0.0f, -2.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.1f, 0.9f, 0.1f), GizmoRenderer::Solid);

		mGizmoRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-10.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		mGizmoRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		mGizmoRenderer->DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		mGizmoRenderer->Flush();
		*/
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
		//Actor* actor = mActorAllocator.AllocateActor(this);
		//int32 index = actor->GetAllocationIndex();
		//if (mActors.size() > index)
		//{
		//	int32 replacingIndex = mActors[index]->GetAllocationIndex();
		//	assert(replacingIndex != index);
		//	if (replacingIndex > index)
		//	{
		//		std::vector<Actor*>::iterator location = mActors.begin() + index;
		//		mActors.insert(location, actor);
		//	}
		//	else
		//	{
		//		std::vector<Actor*>::iterator location = mActors.begin() + index + 1;
		//		mActors.insert(location, actor);
		//	}
		//}
		//else
		Actor* actor = new Actor(this);
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

	Blue::GizmoRenderer* World::GetGizmoRenderer()
	{
		return mGizmoRenderer;
	}

	void World::CommandReloadStencils(std::string aCommand, std::string* aArg, uint32 aArgCount)
	{
	}
}