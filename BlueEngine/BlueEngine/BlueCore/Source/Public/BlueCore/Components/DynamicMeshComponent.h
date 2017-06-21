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

		uint64 ID() override
		{
			return CompileHash("DynamicMeshComponent");
		}

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