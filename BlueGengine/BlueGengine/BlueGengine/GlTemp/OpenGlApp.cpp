//#include "OpenGlApp.h"
//#include <GL/glew.h>
//#include <iostream>
//
//#include "../Imgui/imgui.h"
//#include <glm/glm.hpp>
//#include "../GlmTransformationInclude.h"
//#include <glm/gtc/type_ptr.inl>
//#include "../Shader.h"
//#include <chrono>
//#include "../ApplicationWindow.h"
//#include "../Input.h"
//#include "../timer.h"
//#include "../VertexBuffer.h"
//#include "../MeshLoader.h"
//#include "../Mesh.h"
//#include "../ElementBuffer.h"
//#include "../Texture.h"
//#include "../Light.h"
//#include "../ImageFormat.h"
//#include "../VertexArray.h"
//#include "../Material.h"
//#include "../MaterialManager.h"
//#include "../ForwardRenderer.h"
//#include "../Helpers//MathHelpers.h"
//using namespace std::literals;
//struct Vertex
//{
//	glm::vec3 position;
//	glm::vec2 color;
//};
//namespace BlueGengine
//{
//
//};
//struct LineVertex
//{
//	glm::vec3 position;
//	glm::vec4 color;
//};
//
//glm::mat4 proj;
//glm::mat4 view;
//glm::mat4 model;
//
//
//namespace BlueGengine
//{
//	void OpenGLApp::Run()
//	{
//
//
//		glewExperimental = true;
//		std::cout << "Welcome to BlueGengine" << std::endl;
//		BlueGengine::ApplicationWindow* myWindow = BlueGengine::ApplicationWindow::Create("BlueGengine", 1280, 720, EGraphicsDeviceType::OpenGL);
//		auto retval = glewInit();
//
//		if (retval != GLEW_OK)
//		{
//			auto t = glGetError();
//			std::cout << "Failed to init glew" << std::endl;
//			system("pause");
//			return;
//		}
//
//		ForwardRenderer rend;
//		BlueGengine::Mesh* mesh = BlueGengine::MeshLoader::LoadMeshFromFile("Assets/Models/Cube.obj", "cube");
//
//		if (mesh->NeedToUpdateGpuResource())
//		{
//			mesh->UpdateMeshResources();
//		}
//
//		glEnable(GL_DEPTH_TEST);
//		glFrontFace(GL_CW);
//		glEnable(GL_CULL_FACE);
//		BlueGengine::Shader myShader;
//		myShader.LoadShader("assets/shaders/glsl/SimpleShader.glslv", "assets/shaders/glsl/SimpleShader.glslf");
//		BlueGengine::Shader debugShader;
//		debugShader.LoadShader("assets/shaders/glsl/DebugShader.glslv", "assets/shaders/glsl/DebugShader.glslf");
//		BlueGengine::Shader lightShader;
//		lightShader.LoadShader("assets/shaders/glsl/LightShader.glslv", "assets/shaders/glsl/LightShader.glslf");
//		BlueGengine::Shader testShader;
//		testShader.LoadShader("assets/shaders/glsl/TestShader.glslv", "assets/shaders/glsl/TestShader.glslf");
//
//
//		glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
//		bool loop = true;
//
//		proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
//		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
//		view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//		model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
//
//		int id = myShader.GetShaderID();
//
//
//		char te[512];
//		std::memset(te, 0, 512);
//		float r = 45.0f;
//		int frameCount = 0;
//
//		Timer deltaTimeTimer;
//		Timer fixedUpdateTimer;
//		Timer fpsTimer;
//		deltaTimeTimer.Start();
//		fixedUpdateTimer.Start();
//		fpsTimer.Start();
//		int fps;
//
//
//		GLenum err = glGetError();
//		glLineWidth(2.0f);
//		BlueGengine::Texture* texture = new BlueGengine::Texture;
//		texture->LoadTexture("Assets/Textures/UVTexture.png", BlueGengine::ImageFormat::IF_RGB, BlueGengine::ImageFormat::IF_RGB);
//		std::cout << "Texture width: " << texture->GetWidth() << " Texture height: " << texture->GetWidth() << std::endl;
//		BlueGengine::Light myLight;
//		myLight.position = glm::vec3(1, 0.0f, -1.0f);
//		myLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
//		glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f);
//
//
//		BlueGengine::Material* mat = BlueGengine::MaterialManager::GI()->CreateMaterial();
//		mat->SetShader(&myShader);
//		mat->SetTexture(texture);
//		mat->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//		mat->SetSpecularPower(0.0f);
//		mat->SetAmbientColor(glm::vec4(.1f, .1f, .1f, 1.0f));
//		BlueGengine::Material* mat2 = BlueGengine::MaterialManager::GI()->CreateMaterial();
//		mat2->SetShader(&myShader);
//		mat2->SetTexture(texture);
//		mat2->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
//		mat2->SetSpecularPower(0.0f);
//		mat2->SetAmbientColor(glm::vec4(.1f, .1f, .1f, 1.0f));
//		glm::vec4 diffuseColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		glm::vec4 ambientColor = glm::vec4(.1f, .1f, .1f, 1.0f);
//		float specularPower = 0.0f;
//		//rend.SubmitMesh(mesh, mat, new Transform());
//
//
//		rend.myLight = &myLight;
//
//		while (!myWindow->IsCloseRequest())
//		{
//			float dt = deltaTimeTimer.IntervalS();
//			deltaTimeTimer.Reset();
//			//r += 0.1f;
//			frameCount++;
//
//			if (fpsTimer.IntervalS() >= 1.0f)
//			{
//				fps = frameCount;
//				fpsTimer.Reset();
//				std::cout << fps << std::endl;
//				frameCount = 0;
//			}
//
//
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//			myWindow->Update();
//
//			if (myWindow->IsCloseRequest())
//			{
//				break;
//			}
//
//			if (!BlueGengine::Input::IsKeyboardCaptured())
//			{
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::A))
//				{
//					camPos.x -= 5.0f * dt;
//				}
//				else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::D))
//				{
//					camPos.x += 5.0f * dt;
//				}
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::W))
//				{
//					camPos.z += 5.0f * dt;
//				}
//				else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::S))
//				{
//
//					camPos.z -= 5.0f * dt;
//				}
//
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::LEFT))
//				{
//					myLight.position.x -= 5.0f * dt;
//
//				}
//				else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::RIGHT))
//				{
//					myLight.position.x += 5.0f * dt;
//
//				}
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::UP))
//				{
//					myLight.position.z += 5.0f * dt;
//
//				}
//				else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::DOWN))
//				{
//					myLight.position.z -= 5.0f * dt;
//				}
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::HOME))
//				{
//					myLight.position.y += 5.0f * dt;
//
//				}
//				else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::END))
//				{
//					myLight.position.y -= 5.0f * dt;
//				}
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::ESCAPE))
//				{
//					myWindow->Close();
//				}
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::SPACE))
//				{
//					camPos.y += 5.0f * dt;
//				}
//
//				if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::LEFT_SHIFT))
//				{
//					camPos.y -= 5.0f * dt;
//
//				}
//
//
//			}
//
//			{
//				ImGui::DragFloat4("Diffuse Color", glm::value_ptr(diffuseColor), .01f, 0.0f, 1.0f);
//				ImGui::DragFloat4("Ambient Color", glm::value_ptr(ambientColor), .01f, 0.0f, 1.0f);
//				ImGui::DragFloat("Specular Power", &specularPower, 0.01, 0.0, 1.0f);
//				ImGui::DragFloat3("Light Color", glm::value_ptr(myLight.color), 0.01f, 0.0f, 1.0f);
//
//				mat->SetAmbientColor(ambientColor);
//				mat->SetDiffuseColor(diffuseColor);
//				mat->SetSpecularPower(specularPower);
//			}
//
//
//			glm::vec3 center = camPos;
//			center.z += 1;
//			view = glm::lookAt(camPos, center, glm::vec3(0.0f, 1.0f, 0.0f));
//			rend.Flush();
//			//float radians = glm::radians(r);
//			//model = glm::mat4();
//			//model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//			//model = glm::rotate(model, radians, glm::vec3(0.0f, 1.0f, 0.0f));
//			//myShader.Bind();
//			//id = myShader.GetShaderID();
//			//int loc = glGetUniformLocation(id, "model");
//			//glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
//			//GLenum err = glGetError();
//			//loc = glGetUniformLocation(id, "view");
//			//glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
//			//loc = glGetUniformLocation(id, "projection");
//			//glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
//			//loc = glGetUniformLocation(id, "viewPos");
//			//glUniform3f(loc, camPos.x, camPos.y, camPos.z);
//			//mat->PrepareForDrawing();
//			//myLight.TmpSetUp(&myShader);
//			//loc = glGetUniformLocation(id, "dl.color");
//			//glUniform3f(loc, 1.0, 1.0f, 1.0f);
//			//loc = glGetUniformLocation(id, "dl.direction");
//			//glUniform3f(loc, 0.0f, -1.0f, 0.0f);
//			//mesh->PrepForDrawing();
//			//glDrawElementsInstanced(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, 0, 1);
//			//mesh->UnPrepForDrawing();
//			//mat->Unprep();
//
//			lightShader.Bind();
//			mesh->PrepForDrawing();
//
//			id = lightShader.GetShaderID();
//			int loc = glGetUniformLocation(id, "view");
//			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
//			loc = glGetUniformLocation(id, "projection");
//			glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
//			//myLight.TmpSetUp(&lightShader);
//			loc = glGetUniformLocation(id, "LightPos");
//			glUniform3f(loc, myLight.position.x, myLight.position.y, myLight.position.z);
//			loc = glGetUniformLocation(id, "LightColor");
//			glUniform3f(loc, myLight.color.r, myLight.color.g, myLight.color.b);
//			glDrawElements(GL_TRIANGLES, mesh->GetIndiceCount(), GL_UNSIGNED_INT, nullptr);
//			lightShader.UnBind();
//			mesh->UnPrepForDrawing();
//			lightShader.UnBind();
//
//			ImGui::Render();
//
//			myWindow->Swap();
//
//			if (fixedUpdateTimer.IntervalMS() >= 1.0f / 60.0f)
//			{
//				fixedUpdateTimer.Reset();
//				BlueGengine::Input::Reset();
//			}
//		}
//
//		delete myWindow;
//
//
//		return;
//	}
//
//
//}
//
//
//
//
