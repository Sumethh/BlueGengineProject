#include "BlueCore/Managers/MemoryManager.h"

#include "BlueCore/Core/ActorAllocator.h"
#include "BlueCore/Core/Actor.h"
namespace Blue
{
	const int32 BlockSize = 512000;
	const int32 MaxAllocationsPerPool = (512000 / sizeof(Actor)) - 1;

	struct ActorPool
	{
		ActorPool* next;
		uint32 numAllocations;
		uint32 freeAllocationsLeft;
		ubyte data[MaxAllocationsPerPool * sizeof(Actor)];
	};

	ActorAllocator::ActorAllocator() : mActorPools(nullptr)
	{
		//AllocateNewPool();
	}

	ActorAllocator::~ActorAllocator()
	{
		IMemoryAllocator* largeAllocator = MemoryManager::GI()->GetLargeBlockAllocator();
		ActorPool* pool = mActorPools;
		while (pool)
		{
			ActorPool* next = pool->next;
			largeAllocator->Deallocate(pool, sizeof(ActorPool));
			pool = next;
		}
		mFreeActors.clear();
	}

	Actor* ActorAllocator::AllocateActor(World* aWorld)
	{
		if (mFreeActors.size())
		{
			Actor* actor = mFreeActors.begin()->second;
			mFreeActors.erase(mFreeActors.begin());
			actor = new (actor)Actor(aWorld);
			return actor;
		}
		else
		{
			ActorPool* allocatingPool = mActorPools;
			int index = 0;
			while (!allocatingPool->freeAllocationsLeft)
			{
				if (allocatingPool->next)
					allocatingPool = allocatingPool->next;
				else
				{
					allocatingPool->next = AllocateNewPool();
				}
				index += MaxAllocationsPerPool;
			}

			ubyte* actorLocation = &(allocatingPool->data[allocatingPool->numAllocations * sizeof(Actor)]);
			Actor* returningActor = new (actorLocation)Actor(aWorld);
			returningActor->SetAllocationIndex(index + allocatingPool->numAllocations);

			++allocatingPool->numAllocations;
			--allocatingPool->freeAllocationsLeft;
			return returningActor;
		}
	}

	void ActorAllocator::DeallocateActor(Actor* aActor)
	{
		int32 index = aActor->GetAllocationIndex();
		assert(mFreeActors.find(index) == mFreeActors.end());
		aActor->~Actor();
		mFreeActors[index] = aActor;
	}

	ActorPool* ActorAllocator::AllocateNewPool()
	{
		IMemoryAllocator* largeAllocator = MemoryManager::GI()->GetLargeBlockAllocator();
		ActorPool* newPool = nullptr;

		//void* memory = largeAllocator->Allocate(sizeof(ActorPool), 0);
		void* memory = malloc(sizeof(ActorPool));
		newPool = reinterpret_cast<ActorPool*>(memory);

		newPool->freeAllocationsLeft = MaxAllocationsPerPool;
		newPool->numAllocations = 0;
		newPool->next = nullptr;
		if (!mActorPools)
		{
			mActorPools = newPool;
		}
		else
		{
			ActorPool* end = mActorPools;
			while (end->next)
			{
				end = end->next;
			}
			end->next = newPool;
		}
		return newPool;
	}
}