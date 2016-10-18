#pragma once
#include "ComponentTypes.h"
namespace BlueGengine
{
	class Actor;
	class IRenderer;
	class ActorComponent
	{
		public:
		ActorComponent(Actor* a_owner, EComponentType a_compType);
		virtual ~ActorComponent();

		virtual void BeginPlay();
		virtual void Update(float a_dt);
		virtual void LateUpdate(float a_dt);
		virtual void PreRender();
		virtual void Render(IRenderer* a_renderer);
		virtual void PostRender();
		inline Actor* GetOwner()const { return m_owner; }

		inline EComponentType GetComponentType()const { return m_componentType; }
		protected:
		private:
		EComponentType m_componentType;
		uint64 m_instanceID;
		Actor* m_owner;
	};
}