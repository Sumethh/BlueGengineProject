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
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Renderers/GizmoRenderer.h"
#include "BlueCore/graphics/mesh.h"
#include "BlueCore/Managers/MeshManager.h"
#include <iostream>
#include <glm/glm.hpp>
#include <string>
#include <Imgui/imgui.h>

#include "NavMesh/NavMeshGenerator.h"

class TestApp : public Blue::Application
{
public:
	bool Run() override
	{
		CreateWindow("SandBox", 1920, 1080);
		mWindow->Swap();

		Blue::Application::Run();
		Blue::World myWorld;
		mWindow->SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

		Blue::Actor* camera = myWorld.CreateActor();
		camera->AddComponent<Blue::CameraComponent>();
		camera->AddComponent<Blue::FirstPersonComponent>();
		Blue::Transform trans = camera->GetTransform();
		trans.position = glm::vec3(0, 0, 10);
		trans.rotation = Blue::MathHelpers::QuatFromEuler(glm::vec3(0, 180, 0));
		camera->SetTransform(trans);

		myWorld.BeginPlay();

		// Create navmesh mesh
		Blue::Mesh* navMesh = Blue::MeshManager::GI()->CreateMesh("NavMesh"); 

		std::vector<Blue::Vertex> vertices = { { glm::vec3(0, 0, 0) },{ glm::vec3(0, 0, -10) },{ glm::vec3(-5, 0, -15) },{ glm::vec3(-10, 0, -10) },{ glm::vec3(-10, 0, 0) } };
		std::vector<Blue::uint32> indeces;

		Blue::NavMeshGenerator::TriangulateMesh(vertices, indeces);

		Blue::Vertex* verts = new Blue::Vertex[vertices.size()];
		for (int i = 0; i < vertices.size(); i++)
			verts[i] = vertices[i];
		Blue::uint32* idx = new Blue::uint32[indeces.size()];
		for (int i = 0; i < indeces.size(); i++)
			idx[i] = indeces[i];

		navMesh->Init(verts, vertices.size(), idx, indeces.size());
		navMesh->UpdateMeshResources();

		// ImGui / timer variables
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

			//myWorld.GetGizmoRenderer()->DrawMesh(navMesh, glm::vec3(1, 1, 0));
			Blue::Vertex* navVerts = navMesh->GetVertices();
			Blue::uint32* navIdx = navMesh->GetIndices();
			for (Blue::uint32 i = 0; i < navMesh->GetIndiceCount(); i+=3)
			{
				myWorld.GetGizmoRenderer()->DrawLine(navVerts[navIdx[i]].position    , navVerts[navIdx[i + 1]].position, glm::vec3(1, 0, 0));
				myWorld.GetGizmoRenderer()->DrawLine(navVerts[navIdx[i + 1]].position, navVerts[navIdx[i + 2]].position, glm::vec3(1, 0, 0));
				myWorld.GetGizmoRenderer()->DrawLine(navVerts[navIdx[i + 2]].position, navVerts[navIdx[i]].position		 , glm::vec3(1, 0, 0));
			}

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