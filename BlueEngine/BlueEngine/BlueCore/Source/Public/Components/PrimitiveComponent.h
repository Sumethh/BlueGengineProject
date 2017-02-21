#pragma once
#include "ActorComponent.h"
#include "Graphics/RenderLayer.h"

class MaterialComponent;
class PrimitiveComponent : public ActorComponent
{
	public:
	PrimitiveComponent(Actor* aOwner);
	~PrimitiveComponent();

	void SetMaterialComponent(MaterialComponent* aComponent);
	const uint32 GetMaterialID()const;

	uint64 GetRenderID();

	private:
	MaterialComponent* mMaterialComponent;
	FullScreenLayer mFullScreenLayer;
	ViewportLayer mViewportLayer;
};
