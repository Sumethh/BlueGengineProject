#pragma once
#include "Types.h"
#include <vector>
#include "Managers/StencilManager.h"
namespace BlueCore
{
	class Actor;
	class IRenderer;
	class GizmoRenderer;
	class Stencil;
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

		Actor* CreateActor();
		Actor* CreateActor(Stencil* aStencil);

		void Save(ArchiveObject& aArchiveObject);
		private:
		void CommandReloadStencils(std::string aCommand, std::string* aArg, uint32 aArgCount);
		void CommandSpawnActorFromStencil(std::string aCommand, std::string* aArg, uint32 aArgCount);



		bool mHasBeginPlayBeenCalled;
		std::vector<Actor*> mActors;
		StencilManager mStencilManager;
	};
}

