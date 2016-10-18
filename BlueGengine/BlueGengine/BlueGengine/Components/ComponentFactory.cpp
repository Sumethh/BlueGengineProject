#include "ComponentFactory.h"
#include <map>
#include <functional>

#include "MeshComponent.h"
#include "TransformComponent.h"
#include "MaterialComponent.h"
namespace BlueGengine
{
	class Actor;
	namespace ComponentFactory
	{

		template<class T>
			ActorComponent* GenericComponentCreation(Actor* a_owner)
		{
			return new T(a_owner);
		}


		std::map < EComponentType, std::function<ActorComponent*(Actor*)>> componentConstructors =
		{
			{EComponentType::EMeshComponent, std::bind(GenericComponentCreation<MeshComponent>, std::placeholders::_1)},
			{ EComponentType::ETransformComponent, std::bind(GenericComponentCreation<TransformComponent>, std::placeholders::_1) },

		};

		BlueGengine::ActorComponent* CreateComponent(EComponentType a_type, Actor* a_actor)
		{
			return componentConstructors[a_type](a_actor);
		}

	}
}