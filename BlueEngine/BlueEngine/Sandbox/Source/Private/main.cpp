#include "BlueCore/Core/Application.h"
#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Components/DynamicMeshComponent.h"
#include "BlueCore/Components/ActorComponent.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Components/FirstPersonComponent.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Renderers/SceneRenderer.h"

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <Imgui/imgui.h>
#include <thread>
class TestApp : public Blue::Application
{
public:
	bool Run() override
	{
		CreateWindow("SandBox", 1280, 720);

		Blue::Application::Run();
		Blue::World myWorld;
		mWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		Blue::Actor* cube = myWorld.CreateActor();
		cube->AddComponent<Blue::DynamicMeshComponent>();
		auto cubeTransform = cube->GetTransform();
		cubeTransform.position = glm::vec3(0, 0, 0);
		cube->SetTransform(cubeTransform);

		Blue::Actor* camera = myWorld.CreateActor();
		camera->AddComponent<Blue::CameraComponent>();
		camera->AddComponent<Blue::FirstPersonComponent>();
		auto trans = camera->GetTransform();
		trans.position = glm::vec3(0, 0, -10);
		camera->SetTransform(trans);

		for (Blue::uint32 i = 0; i < 100000; ++i)
		{
			Blue::Actor* actor = myWorld.CreateActor();
			actor->AddComponent<Blue::DynamicMeshComponent>();
			Blue::Transform t;
			t.position.x = i % 100;
			t.position.z = i / 100;
			actor->SetTransform(t);
		}

		myWorld.BeginPlay();
		Blue::AABB bounds = cube->GetActorBounds();
		Blue::Timer dtTimer;
		Blue::SceneRenderer sceneRenderer;
		Blue::uint32 fps = 0;
		Blue::uint32 lastFps = 0;
		Blue::Timer fpsTimer;

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

			Blue::Timer updateTimer;
			updateTimer.Start();
			myWorld.Update(dt);

			ImGui::Text("World::Update: %f ms", (float)updateTimer.IntervalMS());

			Blue::Timer lateUpdateTimer;
			lateUpdateTimer.Start();
			myWorld.LateUpdate(dt);
			float a = (float)lateUpdateTimer.IntervalMS();
			ImGui::Text("World::LateUpdate: %f ms", a);

			Blue::Timer scenePassTimer;
			scenePassTimer.Start();
			sceneRenderer.ConductScenePass(&myWorld);
			ImGui::Text("Scene Pass: %f ms", (float)scenePassTimer.IntervalMS());

			ImGui::End();
			ImGui::Render();
			mWindow->Swap();
			Blue::Input::Reset();
		}

		ShutDown();
		return true;
	}
};

int main(int aArgc, char** aArgv)
{

	TestApp myApp;
	myApp.Run();
	return 0;

}