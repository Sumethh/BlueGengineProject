#include "BlueCore/Core/ApplicationWindow.h"
#include "BlueCore/Input/input.h"
#include "BlueCore/Messaging/WindowResizeMessage.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <Imgui/imgui_impl_glfw_gl3.h>

namespace Blue
{
	void ApplicationWindow::UpdateMousePosition()
	{
		double x, y;
		glfwGetCursorPos(mWindow, &x, &y);
		float oldx, oldY;
		Input::GetMousePosition(oldx, oldY);
		Input::SetMousePosition((float)x, (float)y);
		Input::OnMouseMove((float)(x - oldx), (float)(y - oldY));
	}

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
	}

	void MouseScrollCallBack(GLFWwindow* a_window, double aXOffset, double aYOffset)
	{
		Input::OnMouseScroll((float)aXOffset, (float)aYOffset);
		ImGui_ImplGlfwGL3_ScrollCallback(a_window, aXOffset, aYOffset);
	}

	ApplicationWindow* ApplicationWindow::Create(const char* aTitle, const uint32 a_width, const uint32 aHeight, EGraphicsDeviceType aRenderingType)
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

	ApplicationWindow::ApplicationWindow(const char* aTitle, const uint32 a_width, const uint32 aHeight, EGraphicsDeviceType aRenderingAPI) :
		mWidth(a_width),
		mHeight(aHeight),
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

		ImGui_ImplGlfwGL3_Init(mWindow, true);
		glfwSetKeyCallback(mWindow, KeyCallBack);
		glfwSetMouseButtonCallback(mWindow, MouseButtonCallBack);
		glfwSetScrollCallback(mWindow, MouseScrollCallBack);
		SetVsync(0);
		mCloseRequested = false;
		mMouseInputUpdate.Start();
	}

	ApplicationWindow::~ApplicationWindow()
	{
		glfwDestroyWindow(mWindow);
	}
	void ApplicationWindow::Update()
	{
		ImGui_ImplGlfwGL3_NewFrame();

		if (glfwWindowShouldClose(mWindow))
		{
			mCloseRequested = true;
			return;
		}

		glfwPollEvents();

		if (mMouseInputUpdate.IntervalS() >= 1.0f / 60.0f)
		{
			UpdateMousePosition();
			mMouseInputUpdate.Reset();
		}

		int32 width, height;
		glfwGetWindowSize(mWindow, &width, &height);

		if (width != mWidth || height != mHeight)
		{
			mWidth = width;
			mHeight = height;

			WindowResizeMessage message;
			message.windowHeight = mHeight;
			message.windowWidth = mWidth;
			Message<WindowResizeMessage>::Send(&message);
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
		mCloseRequested = true;
	}

	void ApplicationWindow::SetClearColor(glm::vec4 aColor)
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->SetClearColor(aColor);
	}

	void ApplicationWindow::ClearScreen()
	{
		uint8 bufferBit = static_cast<uint8>(EBufferBit::Color) | static_cast<uint8>(EBufferBit::DepthBit);
		IGraphicsDevice::GetCurrentGraphicsDevice()->ClearBuffer(static_cast<EBufferBit>(bufferBit));
	}

	void ApplicationWindow::MakeContextCurrent()
	{
		BlueAssert(mWindow);

		if(glfwGetCurrentContext() != mWindow)
			glfwMakeContextCurrent(mWindow);

	}

}