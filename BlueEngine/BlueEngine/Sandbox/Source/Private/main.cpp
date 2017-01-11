#include "Core/Application.h"
#include "Core/ApplicationWindow.h"
#include "Input/Input.h"
#include "Hashing/CompileTimeHashing.h"
#include "Core/Timer.h"

#include <iostream>
#include <glm/glm.hpp>

class TestApp : public BlueCore::Application
{
	public:
	bool Run() override
	{
		if (!mWindow)
		{
			CreateWindow("SandBox", 1280, 720);
		}

		BlueCore::Application::Run();

		while (!mWindow->IsCloseRequested())
		{
			if (BlueCore::Input::GetKeyPressed(BlueCore::Input::Key::ESCAPE))
			{
				mWindow->Close();
			}

			BlueCore::Application::Update();
		}

		ShutDown();
		BlueCore::Application::ShutDown();
		return true;
	}
};

int main(int aArgc, char** aArgv)
{
	TestApp myApp;

	myApp.Run();

	glm::vec3 vec;
	int t = 0;


	return 0;
}