#pragma once

namespace Blue
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
	private:
		World* mWorld;

	};
}