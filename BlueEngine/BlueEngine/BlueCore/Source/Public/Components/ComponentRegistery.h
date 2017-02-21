#pragma once
#include "BlueCore.h"
#include "Hashing/CompileTimeHashing.h"

#include <map>
#include <vector>

class ActorComponent;
class Actor;

template<typename T>
ActorComponent*  __ConstructComponent(Actor* aOwner)
{
	return new T(aOwner);
}

struct RegisteredComponentInfo
{
	RegisteredComponentInfo& AddRequiredComponent(uint64 aHash)
	{
		requiredComponents.push_back(aHash);
		return *this;
	}
	uint64 componentHash;
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
		static RegisteredComponentInfo* infoPtr;
		static RegisteredComponentInfo info;
		infoPtr = &info;
		return info;
	}
};


#define RegisterComponentType(type) ComponentRegistery::GI()->RegisterComponent<type>(CompileHash(#type))