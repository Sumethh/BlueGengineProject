#pragma once
#include "Types.h"
#include "BlueCore/Serialization/ArchiveObject.h"
#include "Scene.h"
#include "ActorAllocator.h"
#include <vector>

namespace Blue
{
	class Actor;
	class IRenderer;
	class GizmoRenderer;
	class Stencil;

	class World : public Scene
	{
	public:

		World();
		~World();

		void BeginPlay();
		void Update(float aDt);
		void LateUpdate(float aDt);
		void GizmoDraw(GizmoRenderer* aRenderer);

		Actor* CreateActor();
		Actor* CreateActor(Stencil* aStencil);

		void Save(ArchiveObject& aArchiveObject);
	private:
		void CommandReloadStencils(std::string aCommand, std::string* aArg, uint32 aArgCount);

		bool mHasBeginPlayBeenCalled;
		std::vector<Actor*> mActors;
		ActorAllocator mActorAllocator;
	};
}