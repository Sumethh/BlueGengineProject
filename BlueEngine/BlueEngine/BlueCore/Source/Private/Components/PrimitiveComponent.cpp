#include "Components/PrimitiveComponent.h"
#include "Core/World.h"
#include "Core/Actor.h"
#include "Core/Scene.h"
#include "Components/MaterialComponent.h"
#include "Graphics/Material.h"
#include "Graphics/ImageFormat.h"
PrimitiveComponent::PrimitiveComponent(Actor* aOwner) : ActorComponent(aOwner),
				   mFullScreenLayer(FullScreenLayer::Game),
				   mViewportLayer(ViewportLayer::World)
{
	GetOwner()->GetWorld()->RegisterPrimitiveComponent(this);
}

PrimitiveComponent::~PrimitiveComponent()
{
	Actor* owner = GetOwner();
	Scene* scene = (Scene*)owner->GetWorld();
	scene->DeregisterPimitiveComponent(this);
}

void PrimitiveComponent::SetMaterialComponent(MaterialComponent* aComponent)
{

}

const uint32 PrimitiveComponent::GetMaterialID() const
{
	return 0;
}

glm::uint64 PrimitiveComponent::GetRenderID()
{
	uint64 mReturningID = 0;
	TranslucencyType translucencyType = mMaterialComponent->GetMaterial()->HasAlpha() ? TranslucencyType::Translucent : TranslucencyType::Opaque;
	return mReturningID;
}
