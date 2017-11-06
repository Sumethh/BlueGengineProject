#include "BlueCore/Core/Application.h"
#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Components/DynamicMeshComponent.h"
#include "BlueCore/Components/ActorComponent.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Components/FirstPersonComponent.h"
#include "BlueCore/Components/PointLightComponent.h"
#include "BlueCore/Renderers/SceneRenderer.h"
#include "BlueCore/Managers/MemoryManager.h"
#include "BlueCore/Managers/DebugManager.h"
#include "BlueCore/Input/Input.h"

#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <Imgui/imgui.h>
class TestApp : public Blue::Application
{
public:
	bool Run() override
	{

		CreateWindow("SandBox", 1920, 1080);
		mWindow->Swap();

		Blue::Application::Run();
		Blue::World myWorld;
		mWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		Blue::Actor* camera = myWorld.CreateActor();
		camera->AddComponent<Blue::CameraComponent>();
		camera->AddComponent<Blue::FirstPersonComponent>();
		auto trans = camera->GetTransform();
		trans.position = glm::vec3(0, 0, -10);
		camera->SetTransform(trans);

		Blue::Timer allocTimer;
		allocTimer.Start();
		for (Blue::uint32 i = 0; i < 1; ++i)
		{
			Blue::Actor* actor = myWorld.CreateActor();
			actor->AddComponent<Blue::DynamicMeshComponent>();
			Blue::Transform t;
			t.position.x = static_cast<float>((i % 100) * 2);
			t.position.z = static_cast<float>((i / 100) * 2);
			actor->SetTransform(t);
		}
		double ms = allocTimer.IntervalMS();
		Blue::Log::Info("allocation took: " + std::to_string(ms) + "ms");
		myWorld.BeginPlay();
		Blue::Timer dtTimer;
		Blue::SceneRenderer sceneRenderer;
		Blue::uint32 fps = 0;
		Blue::uint32 lastFps = 0;
		Blue::Timer fpsTimer;
		Blue::DebugManager::GI();
		glm::vec3 position;
		glm::vec3 color;
		while (!mWindow->IsCloseRequested())
		{
			fps++;

			if (fpsTimer.IntervalS() >= 0.5f)
			{
				lastFps = fps;
				fps = 0;
				fpsTimer.Reset();
			}

			float dt = static_cast<float>(dtTimer.IntervalS());
			dtTimer.Reset();
			mWindow->ClearScreen();
			Application::Update();
			ImGui::Begin("Stats");
			ImGui::Text("FPS: %d", lastFps * 2);

			Blue::Timer updateTimer;
			updateTimer.Start();
			myWorld.Update(dt);

			if (Blue::Input::GetKeyDown(Blue::Input::Key::ESCAPE))
				mWindow->Close();

			ImGui::Text("World::Update: %f ms", (float)updateTimer.IntervalMS());

			Blue::Timer lateUpdateTimer;
			lateUpdateTimer.Start();
			myWorld.LateUpdate(dt);
			float a = (float)lateUpdateTimer.IntervalMS();
			ImGui::Text("World::LateUpdate: %f ms", a);
			//ImGui::ShowTestWindow();
			Blue::Timer scenePassTimer;
			scenePassTimer.Start();
			sceneRenderer.ConductScenePass(&myWorld);
			ImGui::Text("Scene Pass: %f ms", (float)scenePassTimer.IntervalMS());
			ImGui::End();
			ImGui::Begin("Create Objects");

			ImGui::InputFloat3("Position", &position.x);
			ImGui::InputFloat3("Color", &color.x);
			if (ImGui::Button("Create Light"))
			{
				Blue::Actor* actor = myWorld.CreateActor();
				Blue::PointLightComponent* light = actor->AddComponent<Blue::PointLightComponent>();
				light->SetColor(color);
				Blue::Transform trans;
				trans.position = position;
				actor->SetTransform(trans);
			}
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
	(void)aArgv;
	(void)aArgc;
	Blue::Log::Info(Blue::Logger("Application Starting Up.") << aArgc << "Arguments passed");
	TestApp myApp;
	myApp.Run();
	return 0;
}