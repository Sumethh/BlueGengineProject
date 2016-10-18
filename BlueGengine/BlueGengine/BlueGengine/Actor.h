#pragma once
#include "Components/ComponentTypes.h"
#include <vector>
namespace BlueGengine
{
	class World;
	class ActorComponent;
	class IRenderer;
	class Actor
	{
		public:
		Actor(World* a_world);
		Actor(const Actor&);
		Actor(Actor&&);
		virtual ~Actor();

		virtual void OnConstruct(EComponentType* a_componentsToAdd, uint32 a_componentCount = 0);
		virtual void BeginPlay();
		virtual void Update(float a_dt);
		virtual void LateUpdate(float a_dt);
		virtual void PreRender();
		virtual void Render(IRenderer* a_renderer);
		virtual void PostRender();


		inline World* GetWorld() { return m_world; }
		private:
		bool m_hasBeginPlayBeenCalled;
		World* m_world;
		uint64 m_instanceID;

		std::vector<ActorComponent*> m_components;
		std::vector<ActorComponent*> m_componentsToAdd;
	};

}