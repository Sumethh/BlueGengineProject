#include "Application.h"
#include "ApplicationWindow.h"
#include "Input.h"
#include "timer.h"
#include "Game.h"
#include "Renderers/ForwardRenderer.h"
#include "GizmoRenderer.h"
#include "imgui/imgui.h"
#include "MeshLoader.h"
#include "Light.h"
#include "Mesh.h"
#include "Log.h"
#include "MeshManager.h"

#include "Systems/TaskSystem.h"
#include "Systems/ASyncLoadingManager.h"
#include <gl/glew.h>
#include <string>

namespace BlueGengine
{


	void DetailedFrameTimings(float aUpdateTime, float aLateUpdateTime, float aPreRenderTime, float aRenderTime, float aPostRenderTime)
	{

		ImGui::Begin("Profiling", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::CollapsingHeader("Detailed Frame Times"))
		{
			ImGui::Text("Update: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", aUpdateTime);


			ImGui::Text("Late Update: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", aLateUpdateTime);


			ImGui::Text("Pre Render: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", aPreRenderTime);


			ImGui::Text("Render: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", aRenderTime);


			ImGui::Text("Post Render: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", aPostRenderTime);
		}

		ImGui::End();
	}

	void UpdateManagers()
	{
		AsyncLoadingManager::Update();
	}

	bool Application::Run()
	{
		mWindow = ApplicationWindow::Create("BlueGengine", 1280, 720, EGraphicsDeviceType::OpenGL);

		//TODO: make this a GraphicsDevice->Init()
		glewInit();

		Timer dtTimer, fpsUpdateTimer;
		Timer updateTimer, LateUpdateTimer, preRenderTimer, renderTimer, postRenderTimer;

		//TODO: Move to more general intiation function
		mGame = new Game();
		glClearColor(0.1f, 0.3f, 1.0f, 1.0f);

		mGame->BeginPlay();
		int fps = 0, displayingFps = 0;
		fpsUpdateTimer.Reset();


		glFrontFace(GL_CW);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glm::mat4 proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);

		glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		BlueGengine::Light myLight;
		myLight.position = glm::vec3(0, 0.0f, -9.0f);
		myLight.color = glm::vec3(1.0f, 1.0f, 1.0f);

		mRenderer = new ForwardRenderer();
		mRenderer->myLight = &myLight;
		mWindow->Update();

		mGizmoRenderer = new GizmoRenderer();
		Input::Reset();
		dtTimer.Reset();

		TaskSystem::Init();

		while (true)
		{
			fps++;
			float dt = (float)dtTimer.IntervalS();
			//TODO: Move to GraphicsDevice
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			dtTimer.Reset();
			mWindow->Update();

			//Need to fix this. (Bug) IMGUI crashes when the close is found in window update
			if (mWindow->IsCloseRequest())
			{
				break;
			}

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
			ImGui::Begin("Frame Info", NULL,  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
			ImGui::Text("Dt: ");
			ImGui::SameLine();
			ImGui::Text("%f %d(fps)", dt, displayingFps);
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


			DetailedFrameTimings((float)updateTime, (float)lateUpdateTime, (float)preRenderTime, (float)renderTime, (float)postRenderTime);
			ImGui::Render();
			mWindow->Swap();
			Input::Reset();
		}

		TaskSystem::Shutdown();
		return true;
	}

}