#pragma once
#include "ActorComponent.h"
namespace BlueGengine
{
	class Mesh;
	class TransformComponent;
	class MaterialComponent;
	class MeshComponent : public ActorComponent
	{
		public:
		MeshComponent(Actor* a_owner);
		~MeshComponent();

		virtual void PreRender() override;
		virtual void Render(IRenderer* a_renderer) override;
		private:
		Mesh* m_mesh;
		TransformComponent* m_transformComponent;
		MaterialComponent* m_materialComponent;
	};

}