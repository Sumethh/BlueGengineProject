#pragma once
#include "Types.h"
#include "NonCopyable.h"
namespace BlueGengine
{
	class ApplicationWindow;
	class Game;
	class Application : public NonCopyable
	{
		public:
		bool Run();

		private:



		ApplicationWindow* m_window;
		Game* m_game;
	};

}