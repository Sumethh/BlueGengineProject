#pragma once
#include "ComponentTypes.h"


namespace BlueGengine
{
	class ActorComponent;
	class Actor;
	namespace ComponentFactory
	{
		ActorComponent* CreateComponent(EComponentType a_type, Actor* a_actor);
	}
}
