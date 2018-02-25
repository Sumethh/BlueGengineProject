#pragma once
#include "BlueCore/Core/Game.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Core/Timer.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Tasks/RenderSceneTask.h"

#include "BlueCore/Serialization/ArchiveObject.h"

#include <Imgui/imgui.h>
//temp
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Components/DynamicMeshComponent.h"
#include "BlueCore/Components/FirstPersonComponent.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Helpers/MathHelpers.h"

namespace Blue
{
	Game::Game() :
		mWorld(nullptr)
	{

	}

	Game::~Game()
	{
		if (mWorld)
		{
			delete mWorld;
		}
	}
	void Game::BeginPlay()
	{
		//TODO load a game config
		mWorld = new World();
		
		Blue::Actor* camera = mWorld->CreateActor();
		camera->AddComponent<Blue::CameraComponent>();
		camera->AddComponent<Blue::FirstPersonComponent>();
		Blue::Transform trans = camera->GetTransform();
		trans.position = glm::vec3(0, 0, 10);
		trans.rotation = Blue::MathHelpers::QuatFromEuler(glm::vec3(0, 180, 0));
		camera->SetTransform(trans);
	
		for (Blue::uint32 i = 0; i < 500; ++i)
		{
			Blue::Actor* actor = mWorld->CreateActor();
			actor->AddComponent<Blue::DynamicMeshComponent>();
			Blue::Transform t;
			t.position.x = static_cast<float>((i % 100) * 2);
			t.position.z = static_cast<float>((i / 100) * 2);
			actor->SetTransform(t);
		}

		mWorld->BeginPlay();
	}
		Timer waiting;

	void Game::Update(float aDt)
	{
		if (mSceneInfoGathered.valid())
			mSceneInfoGathered.wait();

		mWorld->AquireSceneLock();
		mWorld->Update(aDt);
	}

	void Game::LateUpdate(float aDt)
	{
		mWorld->LateUpdate(aDt);
	}

	void Game::SubmitRenderTasks()
	{
		RenderSceneTask* renderTask = new RenderSceneTask();
		renderTask->sceneToRender = reinterpret_cast<Scene*>(mWorld);
		mSceneInfoGathered = renderTask->promise.get_future();

		TaskSystem::SubmitTask(renderTask);
		mWorld->ReleaseSceneLock();
	}

}