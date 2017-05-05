#pragma once
#include "Core/NonCopyable.h"
#include "GraphicsDevice/IGraphicsDevice.h"
#include "Types.h"
#include "timer.h"

#include <glm/vec4.hpp>
struct GLFWwindow;

class   ApplicationWindow : NonCopyable
{
public:
	~ApplicationWindow();
	static ApplicationWindow* Create(const char* aTitle, const uint32 a_width, const uint32 aHeight, EGraphicsDeviceType aRenderingAPI);
	void Update();

	void SetVsync(int aVal);
	void MakeCurrent();
	void Swap();

	static void SetMousePosition(float a_x, float aY);
	static uint32 GetWindowHeight();
	static uint32 GetWindowWidth();

	bool IsCloseRequested() { return mCloseRequested; }
	void Close();

	void SetClearColor(glm::vec4 aColor);
	void ClearScreen();

	static ApplicationWindow* GetCurrentWindow() { return m_currentWindow; }
	inline GLFWwindow* GetUnderlyingWindow()const { return mWindow; }

private:
	void UpdateMousePosition();

	static bool m_apiInit;
	ApplicationWindow(const char* aTitle, const uint32 a_width, const uint32 aHeight, EGraphicsDeviceType aRenderingAPI);

	static ApplicationWindow* m_currentWindow;

	uint32 mWidth, mHeight;
	EGraphicsDeviceType mCurrentRenderingAPI;
	bool mCloseRequested;
	GLFWwindow* mWindow;
	void* mGlConext;

	Timer mMouseInputUpdate;
};
