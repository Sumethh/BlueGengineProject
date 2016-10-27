#include "ApplicationWindow.h"
#include "input.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
namespace BlueGengine
{

	bool ApplicationWindow::m_apiInit;
	ApplicationWindow* ApplicationWindow::m_currentWindow;
	void KeyCallBack(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
	{
		if (a_action == GLFW_PRESS)
		{
			Input::OnKeyDown(a_key);
		}
		else if (a_action == GLFW_RELEASE)
		{
			Input::OnKeyUp(a_key);
		}

		ImGui_ImplGlfwGL3_KeyCallback(a_window, a_key, a_scancode, a_action, a_mods);
	}

	void MousePositionCallback(GLFWwindow* a_window, double a_xpos, double a_yPos)
	{
		float x, y;
		Input::GetMousePosition(x, y);
		Input::SetMousePosition((float)a_xpos, (float)a_yPos);
		Input::OnMouseMove((float)(a_xpos - x), (float)(a_yPos - y));
	}

	void MouseButtonCallBack(GLFWwindow* a_window, int a_button, int a_action, int a_mods)
	{
		if (a_action == GLFW_PRESS)
		{
			Input::OnMouseButtonDown(a_button);
		}
		else if (a_action == GLFW_RELEASE)
		{
			Input::OnMouseButtonUp(a_button);
		}

		ImGui_ImplGlfwGL3_MouseButtonCallback(a_window, a_button, a_action, a_mods);
	}

	void MouseScrollCallBack(GLFWwindow* a_window, double a_xOffset, double a_yOffset)
	{
		Input::OnMouseScroll((float)a_xOffset, (float)a_yOffset);
		ImGui_ImplGlfwGL3_ScrollCallback(a_window, a_xOffset, a_yOffset);
	}

	ApplicationWindow* ApplicationWindow::Create(char* a_title, float a_width, float a_height, EGraphicsDeviceType a_renderingType)
	{

		BlueAssert(a_renderingType != EGraphicsDeviceType::UnIdentified);
		BlueAssert(m_currentWindow == nullptr);

		if (!m_apiInit)
		{
			glfwInit();
			m_apiInit = true;
		}

		if (a_renderingType == EGraphicsDeviceType::OpenGL)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
		else if (a_renderingType == EGraphicsDeviceType::Vulkan)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}


		m_currentWindow = new ApplicationWindow(a_title, a_width, a_height, a_renderingType);
		return m_currentWindow;
	}

	ApplicationWindow::ApplicationWindow(char* a_title, float a_width, float a_height, EGraphicsDeviceType a_renderingAPI) :
	m_width((uint32)a_width),
			m_height((uint32)a_height),
			m_currentRenderingAPI(a_renderingAPI)
	{
		if (m_currentRenderingAPI == EGraphicsDeviceType::OpenGL)
		{
			m_window = glfwCreateWindow(m_width, m_height, a_title, nullptr, nullptr);
			glfwMakeContextCurrent(m_window);

		}
		else if (m_currentRenderingAPI == EGraphicsDeviceType::Vulkan)
		{
			m_window = glfwCreateWindow(m_width, m_height, a_title, nullptr, nullptr);
		}


		ImGui_ImplGlfwGL3_Init(m_window, false);

		glfwSetKeyCallback(m_window, KeyCallBack);
		glfwSetCursorPosCallback(m_window, MousePositionCallback);
		glfwSetMouseButtonCallback(m_window, MouseButtonCallBack);
		glfwSetScrollCallback(m_window, MouseScrollCallBack);
		SetVsync(0);
		m_closeRequested = false;
	}

	ApplicationWindow::~ApplicationWindow()
	{
		glfwDestroyWindow(m_window);
	}
	void ApplicationWindow::Update()
	{
		if (glfwWindowShouldClose(m_window))
		{
			m_closeRequested = true;
			return;
		}

		glfwPollEvents();

		if (m_currentRenderingAPI == EGraphicsDeviceType::OpenGL)
		{
			ImGui_ImplGlfwGL3_NewFrame();
		}

	}

	void ApplicationWindow::SetVsync(int a_val)
	{
		glfwSwapInterval(a_val);
	}

	void ApplicationWindow::MakeCurrent()
	{
		glfwMakeContextCurrent(m_window);
	}

	void ApplicationWindow::Swap()
	{
		glfwSwapBuffers(m_window);
	}

	void ApplicationWindow::SetMousePosition(float a_x, float a_y)
	{
		glfwSetCursorPos(m_currentWindow->m_window, a_x, a_y);
	}

	uint32 ApplicationWindow::GetWindowHeight()
	{
		return m_currentWindow->m_height;
	}

	uint32 ApplicationWindow::GetWindowWidth()
	{
		return m_currentWindow->m_width;
	}

	void ApplicationWindow::Close()
	{
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

}