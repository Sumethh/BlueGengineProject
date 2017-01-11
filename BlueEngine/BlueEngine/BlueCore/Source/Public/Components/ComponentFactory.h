#pragma once
#include "ComponentTypes.h"


namespace BlueCore
{
	class ActorComponent;
	class Actor;
	namespace ComponentFactory
	{
		ActorComponent* CreateComponent(EComponentType aType, Actor* aActor);
	}
}
