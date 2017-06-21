#pragma once
#include "BlueCore/Core/Types.h"

#include <map>
namespace Blue
{
	class Actor;
	class World;
	struct ActorPool;
	class ActorAllocator
	{
	public:
		ActorAllocator();
		~ActorAllocator();
		Actor* AllocateActor(World* aWorld);
		void DeallocateActor(Actor* aActor);
	private:
		ActorPool* AllocateNewPool();
		std::map<uint32, Actor*> mFreeActors;
		ActorPool* mActorPools;
	};
}