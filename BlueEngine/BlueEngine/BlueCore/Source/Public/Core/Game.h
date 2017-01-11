#pragma once

namespace BlueCore
{
	class World;
	class IRenderer;
	class GizmoRenderer;
	class Game
	{
		public:
		Game();
		~Game();
		void BeginPlay();
		void Update(float aDt);
		void LateUpdate(float aDt);
		void PreRender();
		void Render(IRenderer* aRenderer);
		void GizmoDraw(GizmoRenderer* aRenderer);
		void PostRender();
		private:
		World* mWorld;

	};
}