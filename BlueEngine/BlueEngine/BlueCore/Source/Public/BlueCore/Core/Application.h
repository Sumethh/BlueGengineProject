#pragma once
#include "Types.h"
#include "BlueCore/Core/NonCopyable.h"


namespace Blue
{
	class ApplicationWindow;
	class Game;
	class ForwardRenderer;
	class GizmoRenderer;

	class  Application : public NonCopyable
	{
	public:
		Application();
		virtual ~Application();
		virtual bool Run();
		virtual void Update(float aDt);
		virtual void EndUpdate();
		virtual void ShutDown();


		virtual void DisplayWindow();
		virtual void UIPass();
	protected:
		void CreateWindow(const char* aTitle, const uint32 aWidth, const uint32 aHeight);
		static Application* sCurrentApplication;
		ApplicationWindow* mWindow;
		Game* mGame;
		ForwardRenderer* mRenderer;
		GizmoRenderer* mGizmoRenderer;
	};
}