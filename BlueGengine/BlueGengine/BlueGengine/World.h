#pragma once
#include "Types.h"
#include <vector>

namespace BlueGengine
{
	class Actor;
	class IRenderer;
	class GizmoRenderer;
	class World
	{
		public:

		World();
		~World();

		void BeginPlay();
		void Update(float aDt);
		void LateUpdate(float aDt);
		void PreRender();
		void Render(IRenderer* aRenderer);
		void GizmoDraw(GizmoRenderer* aRenderer);
		void PostRender();

		private:
		std::vector<Actor*> mActors;
	};
}

