#pragma once
#include "PrimitiveComponent.h"

namespace Blue
{
	class Mesh;
	class Transformable;
	class MaterialComponent;
	class DynamicMeshComponent : public PrimitiveComponent
	{
	public:
		DynamicMeshComponent(Actor* aOwner);
		~DynamicMeshComponent();

		DEFINE_ACTOR_COMPONENT_BASE_FUNCTIONALITY();

		virtual void PostConstruction() override;
		virtual void BeginPlay() override;

		virtual void CalculateComponentBounds() override;
		virtual void SubmitGeometry(IRenderer* aRenderer) override;
	private:
		void SetMesh(Mesh* aMesh);
		Mesh* mMesh;
		Transformable* mTransformComponent;
		MaterialComponent* mMaterialComponent;
	};
}