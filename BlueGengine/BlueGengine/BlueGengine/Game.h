#pragma once

namespace BlueGengine
{
	class World;
	class Game
	{
		public:
		Game();
		~Game();
		void BeginPlay();
		void Update(float a_dt);
		void LateUpdate(float a_dt);
		void PreRender();
		void Render();
		void PostRender();
		private:
		World* m_world;

	};
}