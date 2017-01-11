#include "Components/DynamicMeshComponent.h"
#include "Components/TransformComponent.h"
#include "Components/MaterialComponent.h"
#include "Components/CameraComponent.h"
#include "Components/FirstPersonComponent.h"
#include "Components/ComponentFactory.h"
#include <map>
#include <functional>

namespace BlueCore
{
	class Actor;
	namespace ComponentFactory
	{

		template<class T>
			ActorComponent* GenericComponentCreation(Actor* aOwner)
		{
			return new T(aOwner);
		}


		std::map < EComponentType, std::function<ActorComponent*(Actor*)>> componentConstructors =
		{
			{EComponentType::EMeshComponent, std::bind(GenericComponentCreation<DynamicMeshComponent>, std::placeholders::_1)},
			{ EComponentType::ETransformComponent, std::bind(GenericComponentCreation<TransformComponent>, std::placeholders::_1) },
			{ EComponentType::EMaterialComponent, std::bind(GenericComponentCreation<MaterialComponent>, std::placeholders::_1) },
			{EComponentType::ECameraComponent, std::bind(GenericComponentCreation<CameraComponent>, std::placeholders::_1)},
			{EComponentType::EFirstPersonComponent, std::bind(GenericComponentCreation<FirstPersonComponent>, std::placeholders::_1)}
		};

		BlueCore::ActorComponent* CreateComponent(EComponentType aType, Actor* aActor)
		{
			return componentConstructors[aType](aActor);
		}

	}
}