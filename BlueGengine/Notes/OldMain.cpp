#if(0)
#include <GL/glew.h>
#include <iostream>
#include <SDL/SDL.h>
#undef main

#include <glm/glm.hpp>
#include "GlmTransformationInclude.h"
#include <glm/gtc/type_ptr.inl>
#include "Shader.h"
#include "imgui/imgui.h"
#include "Imgui/imgui_impl_sdl_gl3.h"
#include <chrono>
#include "OpenGLWindow.h"
#include "Input.h"
#include "timer.h"
#include "VertexBuffer.h"
#include "ModelLoader.h"
#include "Mesh.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "Light.h"
using namespace std::literals;
struct Vertex
{
	glm::vec3 position;
	glm::vec2 color;
};

struct LineVertex
{
	glm::vec3 position;
	glm::vec4 color;
};

glm::mat4 proj;
glm::mat4 view;
glm::mat4 model;

GLfloat boxVertices[] =
{
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

//glm::mat4 positions[4];
glm::vec3 positions[15];
int main()
{
	BlueGengine::Mesh* mesh = BlueGengine::ModelLoader::LoadModelFromFile("Assets/Models/cube.obj");


	glewExperimental = true;
	std::cout << "Welcome to BlueGengine" << std::endl;
	BlueGengine::OpenGLWindow* myWindow = BlueGengine::OpenGLWindow::Create("BlueGengine", 1280, 720);
	auto retval = glewInit();

	if (retval != GLEW_OK)
	{
		auto t = glGetError();
		std::cout << "Failed to init glew" << std::endl;
		system("pause");
		return -1;
	}

//for (int i = 0; i < 4; i++)
//{
//	positions[i] = glm::translate(positions[i], glm::vec3(-4 + i * 2, 0, 0));
//	positions[i] = glm::scale(positions[i], glm::vec3(0.5f, 0.5f, 0.5f));
//}


	for (int i = 0; i < 5; i++)
	{
		positions[i] = glm::vec3(-4 + i * 2, 0, 0);
	}

	for (int i = 5; i < 10; i++)
	{
		positions[i] = glm::vec3(-4 + (i - 5) * 2, 2, 0);
	}

	for (int i = 10; i < 15; i++)
	{
		positions[i] = glm::vec3(-4 + (i - 10) * 2, 0, -2);
	}

	positions[0] = glm::vec3(-1, 0, 0);
	BlueGengine::VertexBuffer::DataDescriptor descs[2];

	for (int i = 0; i < 2; i++)
	{
		descs[i].location = i;
		descs[i].normalized = false;
		descs[i].stride = sizeof(glm::vec3);
		descs[i].instanced = false;
		descs[i].instanceCount = 0;
	}

	descs[0].offset = 0;
	descs[0].count = 3;
	descs[1].offset = sizeof(glm::vec3);
	descs[1].count = 2;

//BlueGengine::VertexBuffer::DataDescriptor instanceDesc[4];

//for (int i = 0; i < 4; i++)
//{
//	instanceDesc[i].location = i + 2;
//	instanceDesc[i].normalized = false;
//	instanceDesc[i].stride = sizeof(glm::mat4);
//	instanceDesc[i].instanced = true;
//	instanceDesc[i].instanceCount = 1;
//	instanceDesc[i].offset = sizeof(glm::vec4) * i;
//	instanceDesc[i].count = 4;
//}

	BlueGengine::VertexBuffer::DataDescriptor instanceDesc;
	instanceDesc.location = 5;
	instanceDesc.normalized = false;
	instanceDesc.stride = sizeof(glm::vec3);
	instanceDesc.instanced = true;
	instanceDesc.instanceCount = 1;
	instanceDesc.offset = 0;
	instanceDesc.count = 3;

	BlueGengine::VertexBuffer myBuff, instancedBuffer;
	BlueGengine::ElementBuffer eBuff;
	GLuint vao;
	ImGui_ImplSdlGL3_Init(myWindow->GetUnderlyingWindow());
	SDL_GL_SetSwapInterval(0);
	glGenVertexArrays(1, &vao);
	eBuff.SetData((void*)mesh->indices.data(), mesh->indices.size() * sizeof(uint32));
	glBindVertexArray(vao);
	myBuff.SetData((void*)mesh->vertices.data(), mesh->vertices.size() * sizeof(BlueGengine::Vertex), BlueGengine::s_vertexDescriptors, BlueGengine::s_vertexDescriptorCount);
	eBuff.Bind();
	instancedBuffer.SetData((void*)positions, sizeof(positions) * 100, &instanceDesc, 1, true);
	glBindVertexArray(0);
	eBuff.UnBind();

	glEnable(GL_DEPTH_TEST);

	BlueGengine::Shader myShader;
	myShader.LoadShader("assets/shaders/glsl/SimpleShader.glslv", "assets/shaders/glsl/SimpleShader.glslf");
	BlueGengine::Shader debugShader;
	debugShader.LoadShader("assets/shaders/glsl/DebugShader.glslv", "assets/shaders/glsl/DebugShader.glslf");
	BlueGengine::Shader lightShader;
	lightShader.LoadShader("assets/shaders/glsl/LightShader.glslv", "assets/shaders/glsl/LightShader.glslf");


	GLuint cubeVao;
	BlueGengine::VertexBuffer cubeBuffer;

	glGenVertexArrays(1, &cubeVao);
	glBindVertexArray(cubeVao);
	cubeBuffer.SetData((void*)mesh->vertices.data(), mesh->vertices.size() * sizeof(BlueGengine::Vertex), BlueGengine::s_vertexDescriptors, BlueGengine::s_vertexDescriptorCount);
	eBuff.Bind();
	glBindVertexArray(0);
	myBuff.UnBind();
	eBuff.UnBind();


	glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	bool loop = true;

	proj = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 100.0f);
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, -9.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));



	int id = myShader.GetShaderID();



	char te[512];
	std::memset(te, 0, 512);
	float r = 45.0f;
	int frameCount = 0;

	Timer deltaTimeTimer;
	Timer fixedUpdateTimer;
	Timer fpsTimer;
	deltaTimeTimer.Start();
	fixedUpdateTimer.Start();
	fpsTimer.Start();
	int fps;


	BlueGengine::VertexBuffer lineBuff;
	uint32 lineVAO;
	glGenVertexArrays(1, &lineVAO);

	BlueGengine::VertexBuffer::DataDescriptor lineDesc[2];

	for (int i = 0; i < 2; i++)
	{
		lineDesc[i].location = i;
		lineDesc[i].normalized = false;
		lineDesc[i].stride = sizeof(LineVertex);
		lineDesc[i].instanced = false;
		lineDesc[i].instanceCount = 1;
	}

	lineDesc[0].offset = 0;
	lineDesc[0].count = 3;

	lineDesc[1].offset = sizeof(glm::vec3);
	lineDesc[1].count = 4;
	glBindVertexArray(lineVAO);
	lineBuff.SetData(NULL, sizeof(LineVertex) * 2, lineDesc, 2, true);
	glBindVertexArray(0);


	GLenum err = glGetError();
	glLineWidth(2.0f);
	lineBuff.BeginMap();
	LineVertex verts[2] =
	{
		LineVertex{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) },
		LineVertex{ glm::vec3(5.0f, 0.0f, 5.0f), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) }

	};
	lineBuff.MapData(verts, sizeof(LineVertex) * 2);
	lineBuff.EndMap();


	BlueGengine::Texture* texture = BlueGengine::Texture::LoadTexture("Assets/Textures/UVTexture.png", BlueGengine::Texture::ImageFormat::IF_RGB, BlueGengine::Texture::ImageFormat::IF_RGB);
	std::cout << "Texture width: " << texture->Width() << " Texture height: " << texture->Height() << std::endl;
	BlueGengine::Light myLight;
	myLight.position = glm::vec3(1, 0.0f, -1.0f);
	myLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 camPos = glm::vec3(0.0f, 0.0f, -10.0f);

	while (!myWindow->IsCloseRequest())
	{
		float dt = deltaTimeTimer.IntervalS();
		deltaTimeTimer.Reset();
		//r += 0.1f;
		frameCount++;

		if (fpsTimer.IntervalS() >= 1.0f)
		{
			fps = frameCount;
			fpsTimer.Reset();
			std::cout << fps << std::endl;
			frameCount = 0;
		}


		SDL_Event events;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myWindow->Update();


		if (!BlueGengine::Input::IsKeyboardCaptured())
		{
			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::A))
			{
				camPos.x -= 1.0 * dt;
			}
			else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::D))
			{
				camPos.x += 1.0 * dt;
			}

			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::W))
			{
				camPos.z += 1.0 * dt;
			}
			else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::S))
			{

				camPos.z -= 1.0 * dt;
			}


			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::LEFT))
			{
				myLight.position.x -= 1.0f * dt;

			}
			else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::RIGHT))
			{
				myLight.position.x += 1.0f * dt;

			}

			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::UP))
			{
				myLight.position.z += 1.0f * dt;

			}
			else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::DOWN))
			{
				myLight.position.z -= 1.0f * dt;
			}

			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::HOME))
			{
				myLight.position.y += 1.0f * dt;

			}
			else if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::END))
			{
				myLight.position.y -= 1.0f * dt;
			}

			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::ESCAPE))
			{
				myWindow->Close();
			}

			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::SPACE))
			{
				camPos.y += 1.0f * dt;
			}

			if (BlueGengine::Input::GetKeyDown(BlueGengine::Input::Key::LSHIFT))
			{
				camPos.y -= 1.0f * dt;

			}
		}

		glm::vec3 center = camPos;
		center.z += 1;
		view = glm::lookAt(camPos, center, glm::vec3(0.0f, 1.0f, 0.0f));
		float radians = glm::radians(r);
		model = glm::mat4();
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, radians, glm::vec3(0.0f, 1.0f, 0.0f));
		ImGui::DragFloat("Rotation: ", &r);
		myShader.Bind();
		id = myShader.GetShaderID();
		int loc = glGetUniformLocation(id, "model");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
		GLenum err = glGetError();
		loc = glGetUniformLocation(id, "view");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
		loc = glGetUniformLocation(id, "projection");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));

		myLight.TmpSetUp(&myShader);
		texture->Bind();
		glBindVertexArray(vao);
		glDrawElementsInstanced(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0, 1);
		glBindVertexArray(0);
		glUseProgram(0);
		texture->UnBind();

		debugShader.Bind();
		int shaderID = debugShader.GetShaderID();
		loc = glGetUniformLocation(shaderID, "view");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
		loc = glGetUniformLocation(shaderID, "projection");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
		glBindVertexArray(lineVAO);
		glDrawArrays(GL_LINES, 0, 2);
		glBindVertexArray(0);
		debugShader.UnBind();

		lightShader.Bind();
		glBindVertexArray(cubeVao);

		id = lightShader.GetShaderID();
		loc = glGetUniformLocation(id, "view");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));
		loc = glGetUniformLocation(id, "projection");
		glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(proj));
		myLight.TmpSetUp(&lightShader);

		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, nullptr);
		lightShader.UnBind();
		glBindVertexArray(0);


		lightShader.UnBind();
		ImGui::Render();

		myWindow->Swap();

		if (fixedUpdateTimer.IntervalMS() >= 1.0f / 60.0f)
		{
			fixedUpdateTimer.Reset();
			BlueGengine::Input::Reset();
		}
	}

	ImGui_ImplSdlGL3_Shutdown();
	delete myWindow;


	return 0;
}
#endif
