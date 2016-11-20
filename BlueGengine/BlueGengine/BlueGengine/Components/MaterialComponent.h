#pragma once
#include "ActorComponent.h"

namespace BlueGengine
{
	class Material;
	class Actor;
	class MaterialComponent : public ActorComponent
	{
		public:
		MaterialComponent(Actor* aOwner);
		~MaterialComponent();

		Material* GetMaterial() const { return mMaterial; }

		private:
		Material* mMaterial;
	};
}