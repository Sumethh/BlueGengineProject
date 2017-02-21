#include "Core/Application.h"
#include "Core/ApplicationWindow.h"
#include "Core/Log.h"
#include "Input/Input.h"
#include "Components/DynamicMeshComponent.h"
#include "Components/ActorComponent.h"
#include "Core/World.h"
#include "Core/Actor.h"


#include <iostream>
#include <glm/glm.hpp>
#include <string>

class TestApp : public Application
{
	public:
	bool Run() override
	{
		CreateWindow("SandBox", 1280, 720);

		Application::Run();
		World myWorld;
		mWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));

		Actor* myActor = myWorld.CreateActor();

		myActor->AddComponent<DynamicMeshComponent>();
		myWorld.BeginPlay();
		Timer dtTimer;

		while (!mWindow->IsCloseRequested())
		{
			float dt = dtTimer.IntervalS();
			dtTimer.Reset();
			mWindow->ClearScreen();
			Application::Update();
			myWorld.Update(dt);
			myWorld.LateUpdate(dt);

			if (Input::GetKeyPressed(Input::Key::ESCAPE))
			{
				mWindow->Close();
				continue;
			}

			mWindow->Swap();
			Input::Reset();
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