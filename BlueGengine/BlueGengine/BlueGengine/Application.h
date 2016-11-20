#pragma once
#include "Types.h"
#include "NonCopyable.h"
namespace BlueGengine
{
	class ApplicationWindow;
	class Game;
	class ForwardRenderer;
	class GizmoRenderer;
	class Application : public NonCopyable
	{
		public:
		bool Run();

		private:



		ApplicationWindow* mWindow;
		Game* mGame;
		ForwardRenderer* mRenderer;
		GizmoRenderer* mGizmoRenderer;
	};

}