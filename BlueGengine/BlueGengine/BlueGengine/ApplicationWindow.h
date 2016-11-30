#pragma once
#include "NonCopyable.h"
#include "Graphics/IGraphicsDevice.h"
#include "Types.h"
#include "timer.h"
struct GLFWwindow;
namespace BlueGengine
{
	class ApplicationWindow : NonCopyable
	{
		public:
		~ApplicationWindow();
		static ApplicationWindow* Create(char* aTitle, float a_width, float aHeight, EGraphicsDeviceType aRenderingAPI);
		void Update();

		void SetVsync(int aVal);
		void MakeCurrent();
		void Swap();

		static void SetMousePosition(float a_x, float aY);
		static uint32 GetWindowHeight();
		static uint32 GetWindowWidth();

		bool IsCloseRequest() { return mCloseRequested; }
		void Close();



		static ApplicationWindow* GetCurrentWindow() { return m_currentWindow; }
		inline GLFWwindow* GetUnderlyingWindow()const { return mWindow; }
		private:

		void UpdateMousePosition();

		static bool m_apiInit;
		ApplicationWindow(char* aTitle, float a_width, float aHeight, EGraphicsDeviceType aRenderingAPI);

		static ApplicationWindow* m_currentWindow;

		uint32 mWidth, mHeight;
		EGraphicsDeviceType mCurrentRenderingAPI;
		bool mCloseRequested;
		GLFWwindow* mWindow;
		void* mGlConext;

		Timer mMouseInputUpdate;
	};
}
