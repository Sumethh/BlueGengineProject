#include "BlueCore/Core/Application.h"
#include "BlueCore/Core/ApplicationWindow.h"

#include "BlueCore/Core/Timer.h"
#include "BlueCore/Core/Game.h"
#include "BlueCore/Input/Input.h"
#include "BlueCore/Renderers/ForwardRenderer.h"
#include "BlueCore/Renderers/GizmoRenderer.h"
#include "BlueCore/Graphics/MeshLoader.h"

#include "BlueCore/Tasks/WindowSwapTask.h"
#include "BlueCore/Tasks/ImguiRenderTask.h"

#include "BlueCore/Graphics/Light.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Managers/MeshManager.h"
#include "BlueCore/GraphicsDevice/GraphicsDeviceFactory.h"
#include "BlueCore/Graphics/RenderThread.h"
#include "BlueCore/Managers/UpdateableManager.h"

#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Managers/ASyncLoadingManager.h"
#include "BlueCore/Managers/MemoryManager.h"
#include "BlueCore/Systems/Console.h"
#include <Imgui/imgui_impl_glfw_gl3.h>
#include <gl/glew.h>
#include <string>
#include <Imgui/Imgui.h>

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
		if(mWindow)
			RenderThread::Init(mWindow);

		mWindow->Update();		
		Input::Reset();
		

		return true;
	}

	void Application::Update(float aDt)
	{
		ImGui_ImplGlfwGL3_NewFrame();
		mWindow->Update();
		UpdateManagers();
		if (mGame)
		{
			mGame->Update(aDt);
			mGame->LateUpdate(aDt);
		}

	}

	void Application::EndUpdate()
	{
		ImGui::Render();
		if (mGame)
		{
			mGame->SubmitRenderTasks();
		}
		UIPass();
		DisplayWindow();
	}

	void Application::ShutDown()
	{
		RenderThread::ShutDown();
		TaskSystem::Shutdown();
	}

	void Application::DisplayWindow()
	{
		if (mWindow)
		{
			WindowSwapTask* task = new WindowSwapTask();
			task->window = mWindow;
			TaskSystem::SubmitTask(task);
		}		
	}

	void Application::UIPass()
	{
		ImGui::Render();
		ImDrawData* drawData = ImGui::GetDrawData();
		ImguiRenderTask* renderTask = new ImguiRenderTask();
		renderTask->drawData.CmdLists = new ImDrawList*[drawData->CmdListsCount];
		renderTask->drawData.CmdListsCount = drawData->CmdListsCount;
		for (sizeInt i = 0; i < drawData->CmdListsCount; ++i)
		{
			ImDrawList* copyToDrawList = renderTask->drawData.CmdLists[i] = new ImDrawList();
			ImDrawList* copyFromDrawList = drawData->CmdLists[i];
			for (auto vtx : copyFromDrawList->VtxBuffer)
			{
				copyToDrawList->VtxBuffer.push_back(vtx);
			}	
			for (auto idx : copyFromDrawList->IdxBuffer)
			{
				copyToDrawList->IdxBuffer.push_back(idx);
			}	
			for (auto cmd : copyFromDrawList->CmdBuffer)
			{
				copyToDrawList->CmdBuffer.push_back(cmd);
			}
		}
		TaskSystem::SubmitTask(renderTask);
	}

	void Application::CreateWindow(const char* aTitle, const uint32 aWidth, const uint32 aHeight)
	{
		mWindow = ApplicationWindow::Create(aTitle, aWidth, aHeight, EGraphicsDeviceType::OpenGL);
	}
}