#pragma once
#include "ActorComponent.h"

namespace Blue
{
	class Material;
	class Actor;
	class MaterialComponent : public ActorComponent
	{
	public:
		DEFINE_ACTOR_COMPONENT_BASE_FUNCTIONALITY();

		MaterialComponent(Actor* aOwner);
		~MaterialComponent();

		virtual void PostConstruction() override;

		Material* GetMaterial() const
		{
			return mMaterial;
		}

	private:
		Material* mMaterial;
	};
}