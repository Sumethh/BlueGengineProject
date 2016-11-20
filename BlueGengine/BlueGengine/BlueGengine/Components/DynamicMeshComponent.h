#pragma once
#include "ActorComponent.h"
namespace BlueGengine
{
	class Mesh;
	class TransformComponent;
	class MaterialComponent;
	class DynamicMeshComponent : public ActorComponent
	{
		public:
		DynamicMeshComponent(Actor* aOwner);
		~DynamicMeshComponent();

		virtual void BeginPlay() override;
		virtual void PreRender() override;
		virtual void Render(IRenderer* aRenderer) override;
		private:
		void SetMesh(Mesh* aMesh) { mMesh = aMesh; }
		Mesh* mMesh;
		TransformComponent* mTransformComponent;
		MaterialComponent* mMaterialComponent;
	};

}