#include "BlueCore/Core/Application.h"
#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Core/Game.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Components/DynamicMeshComponent.h"
#include "BlueCore/Components/ActorComponent.h"
#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Components/FirstPersonComponent.h"
#include "BlueCore/Components/PointLightComponent.h"
#include "BlueCore/Managers/MemoryManager.h"
#include "BlueCore/Managers/DebugManager.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Systems/TaskSystem.h"
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <Imgui/imgui.h>

#include <shared_mutex>

class TestApp : public Blue::Application
{
public:
	bool Run() override
	{
		CreateWindow("SandBox", 1920, 1080);
		mWindow->Swap();

		Blue::Application::Run();
		mGame = new Blue::Game();
		mGame->BeginPlay();

		Blue::Timer dtTimer;
		Blue::DebugManager::GI();

		glm::vec3 position(0.0f, 0.0f, 0.0f);
		glm::vec3 color(0,0,0);
		while (!mWindow->IsCloseRequested())
		{
			float dt = static_cast<float>(dtTimer.IntervalS());			
			dtTimer.Reset();
			Blue::Timer logTimer;

			Blue::Timer updateTimer;
			updateTimer.Start();
			Update(dt);		
			double updateTimeMs = updateTimer.IntervalMS();
			if (Blue::Input::GetKeyDown(Blue::Input::Key::ESCAPE))			
				mWindow->Close();

			
			ImGui::Begin("Stats");
			ImGui::Text("FPS: %f %t DT: %f", 1.0f / dt, dt);
			ImGui::Text("Application::Update: %f ms", static_cast<float>(updateTimeMs));
			ImGui::End();
			EndUpdate();

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
	TestApp* myApp = new TestApp;
	myApp->Run();
	return 0;
}