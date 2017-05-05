#include "Core/Application.h"
#include "Core/ApplicationWindow.h"
#include "Core/Log.h"
#include "Input/Input.h"
#include "Components/DynamicMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Components/CameraComponent.h"
#include "Components/FirstPersonComponent.h"
#include "Core/World.h"
#include "Core/Actor.h"
#include "Renderers/SceneRenderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <Imgui/imgui.h>
#include <thread>
class TestApp : public Application
{
public:
	bool Run() override
	{
		CreateWindow("SandBox", 1280, 720);

		Application::Run();
		World myWorld;
		mWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		Actor* cube = myWorld.CreateActor();
		cube->AddComponent<DynamicMeshComponent>();
		auto cubeTransform = cube->GetTransform();
		cubeTransform.position = glm::vec3(0, 0, 0);
		cube->SetTransform(cubeTransform);

		Actor* camera = myWorld.CreateActor();
		camera->AddComponent<CameraComponent>();
		camera->AddComponent<FirstPersonComponent>();
		auto trans = camera->GetTransform();
		trans.position = glm::vec3(0, 0, -10);
		camera->SetTransform(trans);

		for (uint32 i = 0; i < 100000; ++i)
		{
			Actor* actor = myWorld.CreateActor();
			actor->AddComponent<DynamicMeshComponent>();
			Transform t;
			t.position.x = i % 100;
			t.position.z = i / 100;
			actor->SetTransform(t);
		}

		myWorld.BeginPlay();
		AABB bounds = cube->GetActorBounds();
		Timer dtTimer;
		SceneRenderer sceneRenderer;
		uint32 fps = 0;
		uint32 lastFps = 0;
		Timer fpsTimer;

		while (!mWindow->IsCloseRequested())
		{
			fps++;

			if (fpsTimer.IntervalS() >= 0.5f)
			{
				lastFps = fps;
				fps = 0;
				fpsTimer.Reset();
			}

			float dt = dtTimer.IntervalS();
			dtTimer.Reset();
			mWindow->ClearScreen();
			Application::Update();
			ImGui::Begin("Stats");
			ImGui::Text("FPS: %d", lastFps * 2);

			Timer updateTimer;
			updateTimer.Start();
			myWorld.Update(dt);

			ImGui::Text("World::Update: %f ms", (float)updateTimer.IntervalMS());

			Timer lateUpdateTimer;
			lateUpdateTimer.Start();
			myWorld.LateUpdate(dt);
			float a = (float)lateUpdateTimer.IntervalMS();
			ImGui::Text("World::LateUpdate: %f ms", a);

			Timer scenePassTimer;
			scenePassTimer.Start();
			sceneRenderer.ConductScenePass(&myWorld);
			ImGui::Text("Scene Pass: %f ms", (float)scenePassTimer.IntervalMS());

			ImGui::End();
			ImGui::Render();
			mWindow->Swap();
			Input::Reset();
		}

		ShutDown();
		return true;
	}
};
#include <random>
#include <map>

int main(int aArgc, char** aArgv)
{

	TestApp myApp;
	myApp.Run();
	return 0;

}