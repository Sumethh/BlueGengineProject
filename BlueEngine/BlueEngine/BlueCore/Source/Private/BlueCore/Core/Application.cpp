#include "BlueCore/Core/Application.h"
#include "BlueCore/Core/ApplicationWindow.h"

#include <iostream>
#include "BlueCore/Core/Timer.h"
#include "BlueCore/Core/Game.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Renderers/ForwardRenderer.h"
#include "BlueCore/Renderers/GizmoRenderer.h"
#include "BlueCore/Graphics/MeshLoader.h"

#include "BlueCore/Graphics/Light.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Managers/MeshManager.h"
#include "BlueCore/GraphicsDevice/GraphicsDeviceFactory.h"

#include "BlueCore/Managers/UpdateableManager.h"

#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Managers/ASyncLoadingManager.h"
#include "BlueCore/Managers/MemoryManager.h"
#include "BlueCore/Systems/Console.h"
#include <gl/glew.h>
#include <string>

namespace Blue
{
	Application* Application::sCurrentApplication;

	Application::Application() :
		mWindow(nullptr)
	{
		assert(!sCurrentApplication);
		sCurrentApplication = this;
	}

	Application::~Application()
	{
		delete mWindow;
		MemoryManager::DeleteInstance();
	}

	bool showDetailedTimings = false;

	void CommandShowDetailedTimings(std::string& aCommand, std::string* aArguments, const uint32 aArgCount)
	{
		BlueAssert(aCommand == "DetailedTimings");

		if (aArgCount == 0)
		{
			Log::Info("Detailed timings command requires an int argument");
			return;
		}

		int result = std::stoi(aArguments[0]);

		if (result > 0)
		{
			showDetailedTimings = true;
		}
		else
		{
			showDetailedTimings = false;
		}
	}

	void UpdateManagers()
	{
		UpdatableManager::UpdateManagers();
		Console::Update();
	}

	bool Application::Run()
	{
		TaskSystem::Init();
		Console::Init();
		Log::Init("BlueGengineLog.txt");
		Console::AddCommand("DetailedTimings", std::bind(CommandShowDetailedTimings, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		IGraphicsDevice* gd = GraphicsDeviceFactory::GI()->CreateGraphicsDevice(EGraphicsDeviceType::OpenGL);
		gd->Init();

		glClearColor(0.1f, 0.3f, 1.0f, 1.0f);

		glFrontFace(GL_CW);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glm::mat4 proj = glm::perspective(45.0f, 1920.0f / 1080.0f, 0.1f, 100.0f);

		glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 1.0f, 0.0f));


		mWindow->Update();

		Input::Reset();


		return true;
	}

	void Application::Update()
	{
		mWindow->Update();
		UpdateManagers();
	}

	void Application::EndUpdate()
	{

		//ImGui::Render();
		mWindow->Swap();
	}

	void Application::ShutDown()
	{

		TaskSystem::Shutdown();
	}

	void Application::CreateWindow(const char* aTitle, const uint32 aWidth, const uint32 aHeight)
	{
		mWindow = ApplicationWindow::Create(aTitle, aWidth, aHeight, EGraphicsDeviceType::OpenGL);
	}
}