#pragma once
#include "PrimitiveComponent.h"

class Mesh;
class TransformComponent;
class MaterialComponent;
class DynamicMeshComponent : public PrimitiveComponent
{
	public:
	DynamicMeshComponent(Actor* aOwner);
	~DynamicMeshComponent();

	uint64 ID() override { return CompileHash("Dynamic Mesh Component"); }

	virtual void BeginPlay() override;
	virtual void PreRender() override;
	virtual void Render(IRenderer* aRenderer) override;

	virtual void CalculateComponentBounds() override;
	private:
	void SetMesh(Mesh* aMesh) { mMesh = aMesh; }
	Mesh* mMesh;
	TransformComponent* mTransformComponent;
	MaterialComponent* mMaterialComponent;
};

