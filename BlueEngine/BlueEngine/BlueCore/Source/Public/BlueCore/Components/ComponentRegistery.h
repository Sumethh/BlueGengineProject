#pragma once
#include "BlueCore/BlueCore.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Hashing/CompileTimeHashing.h"
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
		//IMemoryAllocator* smallAllocator = MemoryManager::GI()->GetSmallBlockAllocator();
		//return new (smallAllocator->Allocate(sizeof(T), 0)) T(aOwner);
		return new T(aOwner);
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
		__forceinline RegisteredComponentInfo& RegisterComponent()
		{
			RegisteredComponentInfo& info = GetStaticComponentInfo<T>();
			info.Construct = &__ConstructComponent<T>;
			T* component = static_cast<T*>(info.Construct(nullptr));

			mRegisteryMap.emplace(component->ID(), info);
			info.componentHash = component->ID();
			info.componentSize = sizeof(T);
			T::__ComponentSize = info.componentSize;
			Blue::Log::Info("Registering Component with ID: " + std::to_string(info.componentHash) + " Size: " + std::to_string(sizeof(T)));

			uint64 size(component->ComponentSize());
			//IMemoryAllocator* smallBlockAllocator = MemoryManager::GI()->GetSmallBlockAllocator();
			//
			//component->~T();
			//smallBlockAllocator->Deallocate((void*)component, size);
			delete component;
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

#define RegisterComponentType(type) Blue::ComponentRegistery::GI()->RegisterComponent<type>()