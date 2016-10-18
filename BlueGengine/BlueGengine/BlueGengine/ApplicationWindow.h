#pragma once
#include "NonCopyable.h"
#include "GraphicsDevice.h"
#include "Types.h"
struct GLFWwindow;
namespace BlueGengine
{
	class ApplicationWindow : NonCopyable
	{
	public:
		~ApplicationWindow();
		static ApplicationWindow* Create(char* a_title, float a_width, float a_height, EGraphicsDeviceType a_renderingAPI);
		void Update();

		void SetVsync(int a_val);
		void MakeCurrent();
		void Swap();

		bool IsCloseRequest() { return m_closeRequested; }
		void Close();

		inline GLFWwindow* GetUnderlyingWindow()const { return m_window; }
	private:

		static bool m_apiInit;
		ApplicationWindow(char* a_title, float a_width, float a_height, EGraphicsDeviceType a_renderingAPI);

		uint32 m_width, m_height;
		EGraphicsDeviceType m_currentRenderingAPI;
		bool m_closeRequested;
		GLFWwindow* m_window;
		void* m_glConext;
	};
}
