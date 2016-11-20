#pragma once
#include "ComponentTypes.h"
namespace BlueGengine
{
	class Actor;
	class IRenderer;
	class GizmoRenderer;
	class ActorComponent
	{
		public:
		ActorComponent(Actor* aOwner, EComponentType aCompType);
		virtual ~ActorComponent();

		virtual void BeginPlay();
		virtual void Update(float aDt);
		virtual void LateUpdate(float aDt);
		virtual void PreRender();
		virtual void Render(IRenderer* aRenderer);
		virtual void OnGizmoRender(GizmoRenderer* aRenderer);
		virtual void PostRender();


		inline Actor* GetOwner()const { return mOwner; }

		inline bool Enabled()const { return mEnabled; }
		inline bool SetEnabled(bool aNewEnabled) { mEnabled = aNewEnabled; }

		inline EComponentType GetComponentType()const { return mComponentType; }
		protected:
		private:
		bool mEnabled;
		EComponentType mComponentType;
		uint64 mInstanceID;
		Actor* mOwner;
	};
}