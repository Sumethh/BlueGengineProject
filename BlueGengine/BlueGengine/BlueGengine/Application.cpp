#include "Application.h"
#include "ApplicationWindow.h"
#include "Input.h"
#include "timer.h"
#include "Game.h"
#include "ForwardRenderer.h"
#include "imgui/imgui.h"
#include "ModelLoader.h"
#include "Light.h"
#include "Mesh.h"
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
			ImGui::Text("%f ms", a_updateTime);


			ImGui::Text("Late Update: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", a_lateUpdateTime);


			ImGui::Text("Pre Render: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", a_preRenderTime);


			ImGui::Text("Render: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", a_renderTime);


			ImGui::Text("Post Render: ");
			ImGui::SameLine();
			ImGui::Text("%f ms", a_postRenderTime);
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
		Mesh* m = ModelLoader::LoadModelFromFile("Assets/Models/Cube.obj");

		if (m->NeedToUpdateGpuResource())
		{
			m->UpdateMeshResources();
		}

		m_game->BeginPlay();
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

		m_renderer = new ForwardRenderer();
		m_renderer->myLight = &myLight;
		m_window->Update();
		Input::Reset();
		dtTimer.Reset();
		while (true)
		{
			fps++;
			float dt = (float)dtTimer.IntervalS();
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
				displayingFps = (int)(fps * (1 / elapsed));
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
			double updateTime = updateTimer.IntervalMS();

			//Game LateUpdate
			LateUpdateTimer.Reset();
			m_game->LateUpdate(dt);
			double lateUpdateTime = LateUpdateTimer.IntervalMS();

			//Game PreRender
			preRenderTimer.Reset();
			m_game->PreRender();
			double preRenderTime = preRenderTimer.IntervalMS();

			//Game Render
			renderTimer.Reset();
			m_game->Render(m_renderer);
			double renderTime = renderTimer.IntervalMS();

			//Game PostRender
			postRenderTimer.Reset();
			m_game->PostRender();
			double postRenderTime = postRenderTimer.IntervalMS();


			DetailedFrameTimings((float)updateTime, (float)lateUpdateTime, (float)preRenderTime, (float)renderTime, (float)postRenderTime);
			m_renderer->Flush();
			ImGui::Render();
			m_window->Swap();
			Input::Reset();
		}

		return true;
	}

}