#pragma once
#include "BlueCore/BlueCore.h"
#include "BlueCore/Hashing/CompileTimeHashing.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Managers/MemoryManager.h"
#include <map>
#include <vector>

namespace Blue
{
	class ActorComponent;
	class Actor;

	template<typename T>
	ActorComponent*  __ConstructComponent(Actor* aOwner)
	{
		BlockAllocator& smallAllocator = MemoryManager::GI()->GetSmallBlockAllocator();
		return new (smallAllocator.Allocate(sizeof(T), 0)) T(aOwner);
	}

	struct RegisteredComponentInfo
	{
		RegisteredComponentInfo& AddRequiredComponent(uint64 aHash);
		uint64 componentHash;
		size_t componentSize;
		ActorComponent* (*Construct)(Actor*);
		std::vector<uint64> requiredComponents;
	};

	class ComponentRegistery
	{
	public:
		ComponentRegistery();
		~ComponentRegistery();
		void Init();

		template<typename T>
		RegisteredComponentInfo& RegisterComponent(uint64 aHash)
		{
			RegisteredComponentInfo& info = GetStaticComponentInfo<T>();
			mRegisteryMap.emplace(aHash, info);
			info.Construct = &__ConstructComponent<T>;
			info.componentHash = aHash;
			info.componentSize = sizeof(T);
			Blue::Log::Info("Registering Component with ID: " + std::to_string(aHash) + " Size: " + std::to_string(sizeof(T)));
			return info;
		}

		template<typename T>
		ActorComponent* Construct(Actor* aOwner)
		{
			return GetStaticComponentInfo<T>().Construct(aOwner);
		}

		ActorComponent* Construct(uint64 aID, Actor* aOwner)
		{
			return mRegisteryMap.find(aID)->second.Construct(aOwner);
		}

		const RegisteredComponentInfo& GetComponentInfo(uint64 aID)
		{
			return mRegisteryMap.find(aID)->second;
		}

		template<typename T>
		const RegisteredComponentInfo& GetComponentInfo()
		{
			return GetStaticComponentInfo<T>();
		}

		static ComponentRegistery* GI()
		{
			if (!mInstance)
			{
				mInstance = new ComponentRegistery();
				mInstance->Init();
			}

			return mInstance;
		}
	private:
		static ComponentRegistery* mInstance;
		std::map<uint64, RegisteredComponentInfo&> mRegisteryMap;

		template<typename T>
		RegisteredComponentInfo& GetStaticComponentInfo()
		{
			static RegisteredComponentInfo info;
			return info;
		}
	};
}

#define RegisterComponentType(type) Blue::ComponentRegistery::GI()->RegisterComponent<type>(CompileHash(#type))