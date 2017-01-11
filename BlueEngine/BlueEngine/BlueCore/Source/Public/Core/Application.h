#pragma once
#include "Types.h"
#include "Core/NonCopyable.h"
namespace BlueCore
{
	class ApplicationWindow;
	class Game;
	class ForwardRenderer;
	class GizmoRenderer;


	class BLUECORE_API Application : public NonCopyable
	{
		public:
		Application();
		virtual ~Application();
		virtual bool Run();

		protected:
		virtual void Update();
		virtual void ShutDown();
		void CreateWindow(const char* aTitle, const uint32 aWidth, const uint32 aHeight);

		ApplicationWindow* mWindow;
		Game* mGame;
		ForwardRenderer* mRenderer;
		GizmoRenderer* mGizmoRenderer;
	};

}