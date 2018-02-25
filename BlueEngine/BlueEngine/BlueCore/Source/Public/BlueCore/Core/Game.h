#pragma once
#include <future>
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
		void SubmitRenderTasks();
	private:
		World* mWorld;
		std::future<bool> mSceneInfoGathered;
	};
}