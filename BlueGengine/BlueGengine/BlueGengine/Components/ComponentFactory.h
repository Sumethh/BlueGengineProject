#pragma once
#include "ComponentTypes.h"


namespace BlueGengine
{
	class ActorComponent;
	class Actor;
	namespace ComponentFactory
	{
		ActorComponent* CreateComponent(EComponentType aType, Actor* aActor);
	}
}
