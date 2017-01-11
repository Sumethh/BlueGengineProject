#include "Core/Application.h"
#include "Core/ApplicationWindow.h"

#include <iostream>
#include "Core/Timer.h"
#include "Core/Game.h"
#include "Input/Input.h"
#include "Renderers/ForwardRenderer.h"
#include "Renderers/GizmoRenderer.h"
#include "Graphics/MeshLoader.h"
#include "imgui/imgui.h"
#include "Graphics/Light.h"
#include "Graphics/Mesh.h"
#include "Core/Log.h"
#include "Managers/MeshManager.h"
#include "GraphicsDevice/GraphicsDeviceFactory.h"

#include "Managers/UpdateableManager.h"

#include "Systems/TaskSystem.h"
#include "Managers/ASyncLoadingManager.h"
#include "Systems/Console.h"
#include <gl/glew.h>
#include <string>

namespace BlueCore
{

	Application::Application() :
	mWindow(nullptr)
	{

	}

	Application::~Application()
	{
		delete mWindow;
	}

	bool showDetailedTimings = false;

	void CommandShowDetailedTimings(std::string& aCommand, std::string* aArguments, const uint32 aArgCount)
	{
		BlueAssert(aCommand == "DetailedTimings");

		if (aArgCount == 0)
		{
			Log::LogInfo("Detailed timings command requires an int argument");
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

	void DetailedFrameTimings(float aUpdateTime, float aLateUpdateTime, float aPreRenderTime, float aRenderTime, float aPostRenderTime)
	{
		ImGui::Begin("Profiling", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Text("Update: ");
		ImGui::SameLine();
		ImGui::Text(" % f ms", aUpdateTime);

		ImGui::Text("Late Update: ");
		ImGui::SameLine();
		ImGui::Text(" % f ms", aLateUpdateTime);

		ImGui::Text("Pre Render: ");
		ImGui::SameLine();
		ImGui::Text(" % f ms", aPreRenderTime);

		ImGui::Text("Render: ");
		ImGui::SameLine();
		ImGui::Text(" % f ms", aRenderTime);

		ImGui::Text("Post Render: ");
		ImGui::SameLine();
		ImGui::Text(" % f ms", aPostRenderTime);
		ImGui::End();
	}

	void UpdateManagers()
	{
		UpdatableManager::UpdateManagers();
		Console::Update();
	}

	Timer dtTimer, fpsUpdateTimer;
	Timer updateTimer, LateUpdateTimer, preRenderTimer, renderTimer, postRenderTimer;
	int fps = 0, displayingFps = 0;

	bool Application::Run()
	{
		std::cout << "Application::Run was called" << std::endl;
		TaskSystem::Init();
		Console::Init();
		Log::Init("BlueGengineLog.txt");
		Console::AddCommand("DetailedTimings", std::bind(CommandShowDetailedTimings, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		IGraphicsDevice* gd = GraphicsDeviceFactory::GI()->CreateGraphicsDevice(EGraphicsDeviceType::OpenGL);
		gd->Init();


		//TODO: Move to more general intiation function
		mGame = new Game();
		glClearColor(0.1f, 0.3f, 1.0f, 1.0f);

		mGame->BeginPlay();
		fpsUpdateTimer.Reset();


		glFrontFace(GL_CW);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glm::mat4 proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

		glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		mRenderer = new ForwardRenderer();
		mWindow->Update();

		mGizmoRenderer = new GizmoRenderer();
		Input::Reset();
		dtTimer.Reset();


		return true;
	}

	void Application::Update()
	{
		fps++;
		float dt = (float)dtTimer.IntervalS();
		//TODO: Move to GraphicsDevice
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		dtTimer.Reset();
		mWindow->Update();

		////Need to fix this. (Bug) IMGUI crashes when the close is found in window update
		//if (mWindow->IsCloseRequest())
		//{
		//	break;
		//}

		//TODO: Add diagnostics Class
		double elapsed = fpsUpdateTimer.IntervalS();

		if (elapsed >= 0.25f)
		{
			displayingFps = (int)(fps * (1 / elapsed));
			fps = 0;
			fpsUpdateTimer.Reset();
		}

		UpdateManagers();
		ImGui::SetNextWindowPos(ImVec2(5, 5));
		ImGui::Begin("Frame Info", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
		ImGui::Text("Dt: ");
		ImGui::SameLine();
		ImGui::Text(" % f % d(fps)", dt, displayingFps);
		ImGui::End();


		//Game Update
		updateTimer.Reset();
		mGame->Update(dt);
		double updateTime = updateTimer.IntervalMS();

		//Game LateUpdate
		LateUpdateTimer.Reset();
		mGame->LateUpdate(dt);
		double lateUpdateTime = LateUpdateTimer.IntervalMS();

		TaskSystem::Sync();

		//Game PreRender
		preRenderTimer.Reset();
		mGame->PreRender();
		double preRenderTime = preRenderTimer.IntervalMS();

		//Game Render
		renderTimer.Reset();
		mGame->Render(mRenderer);
		mRenderer->Flush();

		double renderTime = renderTimer.IntervalMS();

		//Game Gizmo
		mGame->GizmoDraw(mGizmoRenderer);
		//Game PostRender
		postRenderTimer.Reset();
		mGame->PostRender();
		double postRenderTime = postRenderTimer.IntervalMS();

		TaskSystem::Sync();

		if (showDetailedTimings)
		{
			DetailedFrameTimings((float)updateTime, (float)lateUpdateTime, (float)preRenderTime, (float)renderTime, (float)postRenderTime);
		}

		ImGui::Render();
		mWindow->Swap();
		Input::Reset();
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