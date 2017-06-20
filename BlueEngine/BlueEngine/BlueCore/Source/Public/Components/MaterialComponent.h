#pragma once
#include "ActorComponent.h"

namespace Blue
{
	class Material;
	class Actor;
	class MaterialComponent : public ActorComponent
	{
	public:
		MaterialComponent(Actor* aOwner);
		~MaterialComponent();

		uint64 ID() override
		{
			return CompileHash("MaterialComponent");
		}
		Material* GetMaterial() const
		{
			return mMaterial;
		}

	private:
		Material* mMaterial;
	};
}