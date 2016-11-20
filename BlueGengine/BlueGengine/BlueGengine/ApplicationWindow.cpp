#include "ApplicationWindow.h"
#include "input.h"
#include "imgui/imgui_impl_glfw_gl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
namespace BlueGengine
{

	bool ApplicationWindow::m_apiInit;
	ApplicationWindow* ApplicationWindow::m_currentWindow;
	void KeyCallBack(GLFWwindow* a_window, int aKey, int aScancode, int aAction, int aMods)
	{
		if (aAction == GLFW_PRESS)
		{
			Input::OnKeyDown(aKey);
		}
		else if (aAction == GLFW_RELEASE)
		{
			Input::OnKeyUp(aKey);
		}

		ImGui_ImplGlfwGL3_KeyCallback(a_window, aKey, aScancode, aAction, aMods);
	}

	void MousePositionCallback(GLFWwindow* a_window, double a_xpos, double aYPos)
	{
		float x, y;
		Input::GetMousePosition(x, y);
		Input::SetMousePosition((float)a_xpos, (float)aYPos);
		Input::OnMouseMove((float)(a_xpos - x), (float)(aYPos - y));
	}

	void MouseButtonCallBack(GLFWwindow* a_window, int aButton, int aAction, int aMods)
	{
		if (aAction == GLFW_PRESS)
		{
			Input::OnMouseButtonDown(aButton);
		}
		else if (aAction == GLFW_RELEASE)
		{
			Input::OnMouseButtonUp(aButton);
		}

		ImGui_ImplGlfwGL3_MouseButtonCallback(a_window, aButton, aAction, aMods);
	}

	void MouseScrollCallBack(GLFWwindow* a_window, double a_xOffset, double aYOffset)
	{
		Input::OnMouseScroll((float)a_xOffset, (float)aYOffset);
		ImGui_ImplGlfwGL3_ScrollCallback(a_window, a_xOffset, aYOffset);
	}

	ApplicationWindow* ApplicationWindow::Create(char* aTitle, float a_width, float aHeight, EGraphicsDeviceType aRenderingType)
	{

		BlueAssert(aRenderingType != EGraphicsDeviceType::UnIdentified);
		BlueAssert(m_currentWindow == nullptr);

		if (!m_apiInit)
		{
			glfwInit();
			m_apiInit = true;
		}

		if (aRenderingType == EGraphicsDeviceType::OpenGL)
		{
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		}
		else if (aRenderingType == EGraphicsDeviceType::Vulkan)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		}


		m_currentWindow = new ApplicationWindow(aTitle, a_width, aHeight, aRenderingType);
		return m_currentWindow;
	}

	ApplicationWindow::ApplicationWindow(char* aTitle, float a_width, float aHeight, EGraphicsDeviceType aRenderingAPI) :
	mWidth((uint32)a_width),
		   mHeight((uint32)aHeight),
		   mCurrentRenderingAPI(aRenderingAPI)
	{
		if (mCurrentRenderingAPI == EGraphicsDeviceType::OpenGL)
		{
			mWindow = glfwCreateWindow(mWidth, mHeight, aTitle, nullptr, nullptr);
			glfwMakeContextCurrent(mWindow);

		}
		else if (mCurrentRenderingAPI == EGraphicsDeviceType::Vulkan)
		{
			mWindow = glfwCreateWindow(mWidth, mHeight, aTitle, nullptr, nullptr);
		}


		ImGui_ImplGlfwGL3_Init(mWindow, false);

		glfwSetKeyCallback(mWindow, KeyCallBack);
		glfwSetCursorPosCallback(mWindow, MousePositionCallback);
		glfwSetMouseButtonCallback(mWindow, MouseButtonCallBack);
		glfwSetScrollCallback(mWindow, MouseScrollCallBack);
		SetVsync(0);
		mCloseRequested = false;
	}

	ApplicationWindow::~ApplicationWindow()
	{
		glfwDestroyWindow(mWindow);
	}
	void ApplicationWindow::Update()
	{
		if (glfwWindowShouldClose(mWindow))
		{
			mCloseRequested = true;
			return;
		}

		glfwPollEvents();

		if (mCurrentRenderingAPI == EGraphicsDeviceType::OpenGL)
		{
			ImGui_ImplGlfwGL3_NewFrame();
		}

	}

	void ApplicationWindow::SetVsync(int aVal)
	{
		glfwSwapInterval(aVal);
	}

	void ApplicationWindow::MakeCurrent()
	{
		glfwMakeContextCurrent(mWindow);
	}

	void ApplicationWindow::Swap()
	{
		glfwSwapBuffers(mWindow);
	}

	void ApplicationWindow::SetMousePosition(float a_x, float aY)
	{
		glfwSetCursorPos(m_currentWindow->mWindow, a_x, aY);
	}

	uint32 ApplicationWindow::GetWindowHeight()
	{
		return m_currentWindow->mHeight;
	}

	uint32 ApplicationWindow::GetWindowWidth()
	{
		return m_currentWindow->mWidth;
	}

	void ApplicationWindow::Close()
	{
		glfwSetWindowShouldClose(mWindow, GLFW_TRUE);
	}

}