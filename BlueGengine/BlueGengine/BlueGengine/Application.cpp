#include "Application.h"
#include "ApplicationWindow.h"
#include "Input.h"
#include "timer.h"
#include "Game.h"

#include "imgui/imgui.h"

#include <gl/glew.h>
#include <string>
namespace BlueGengine
{

	void DetailedFrameTimings(float a_updateTime, float a_lateUpdateTime, float a_preRenderTime, float a_renderTime, float a_postRenderTime)
	{

		ImGui::Begin("Profiling", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		if (ImGui::CollapsingHeader("Detailed Frame Times"))
		{
			ImGui::Text("Update: ");
			ImGui::SameLine();
			ImGui::Text("%f s", a_updateTime);


			ImGui::Text("Late Update: ");
			ImGui::SameLine();
			ImGui::Text("%f s", a_lateUpdateTime);


			ImGui::Text("Pre Render: ");
			ImGui::SameLine();
			ImGui::Text("%f s", a_preRenderTime);


			ImGui::Text("Render: ");
			ImGui::SameLine();
			ImGui::Text("%f s", a_renderTime);


			ImGui::Text("Post Render: ");
			ImGui::SameLine();
			ImGui::Text("%f s", a_postRenderTime);
		}

		ImGui::End();
	}

	bool Application::Run()
	{
		m_window = ApplicationWindow::Create("BlueGengine", 1280, 720, EGraphicsDeviceType::OpenGL);

		//TODO: make this a GraphicsDevice->Init()
		glewInit();

		Timer dtTimer, fpsUpdateTimer;
		Timer updateTimer, LateUpdateTimer, preRenderTimer, renderTimer, postRenderTimer;

		//TODO: Move to more general intiation function
		m_game = new Game();
		glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
		m_game->BeginPlay();
		int fps = 0, displayingFps = 0;
		fpsUpdateTimer.Reset();

		while (true)
		{
			fps++;
			float dt = dtTimer.IntervalS();
			//TODO: Move to GraphicsDevice
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			dtTimer.Reset();
			m_window->Update();

			//Need to fix this. (Bug) IMGUI crashes when the close is found in window update
			if (m_window->IsCloseRequest())
			{
				return true;
			}

			//TODO: Add diagnostics Class
			double elapsed = fpsUpdateTimer.IntervalS();

			if (elapsed >= 0.25f)
			{
				displayingFps = fps * (1 / elapsed);
				fps = 0;
				fpsUpdateTimer.Reset();
			}

			ImGui::SetNextWindowPos(ImVec2(5, 5));
			ImGui::Begin("Frame Info", NULL,  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
			ImGui::Text("Dt: ");
			ImGui::SameLine();
			ImGui::Text("%f %d(fps)", dt, displayingFps);
			ImGui::End();
			//Game Update
			updateTimer.Reset();
			m_game->Update(dt);
			double updateTime = updateTimer.IntervalS();

			//Game LateUpdate
			LateUpdateTimer.Reset();
			m_game->LateUpdate(dt);
			double lateUpdateTime = LateUpdateTimer.IntervalS();

			//Game PreRender
			preRenderTimer.Reset();
			m_game->PreRender();
			double preRenderTime = preRenderTimer.IntervalS();

			//Game Render
			renderTimer.Reset();
			m_game->Render();
			double renderTime = renderTimer.IntervalS();

			//Game PostRender
			postRenderTimer.Reset();
			m_game->PostRender();
			double postRenderTime = postRenderTimer.IntervalS();


			DetailedFrameTimings(updateTime, lateUpdateTime, preRenderTime, renderTime, postRenderTime);

			ImGui::Render();
			m_window->Swap();
			Input::Reset();
		}

		return true;
	}

}