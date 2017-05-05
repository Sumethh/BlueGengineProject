#pragma once
#include "ActorComponent.h"
#include "Graphics/RenderLayer.h"
#include "Core/Transformable.h"

class MaterialComponent;
class Material;
class IRenderer;

class PrimitiveComponent : public ActorComponent, public Transformable
{
	public:
	PrimitiveComponent(Actor* aOwner);
	~PrimitiveComponent();


	Material* GetMaterial();

	bool IsTranslucent();

	uint64 GetRenderID(const Transform& aInverseCameraTransform);

	virtual void SubmitGeometry(IRenderer* aRenderer) = 0;

	glm::mat4 GetWorldMatrix();

	private:

	MaterialComponent* mMaterialComponent;
	EFullScreenLayer mFullScreenLayer;
	EViewportLayer mViewportLayer;
};
