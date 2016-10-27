#pragma once
#include "ActorComponent.h"

namespace BlueGengine
{
	class Material;
	class Actor;
	class MaterialComponent : public ActorComponent
	{
		public:
		MaterialComponent(Actor* a_owner);
		~MaterialComponent();

		Material* GetMaterial() const { return m_material; }

		private:
		Material* m_material;
	};
}