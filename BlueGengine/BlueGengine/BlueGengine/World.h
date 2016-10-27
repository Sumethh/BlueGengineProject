#pragma once
#include "Types.h"
#include <vector>

namespace BlueGengine
{
	class Actor;
	class IRenderer;
	class World
	{
		public:

		World();
		~World();

		void BeginPlay();
		void Update(float a_dt);
		void LateUpdate(float a_dt);
		void PreRender();
		void Render(IRenderer* a_renderer);
		void PostRender();

		private:
		std::vector<Actor*> m_actors;
	};
}

