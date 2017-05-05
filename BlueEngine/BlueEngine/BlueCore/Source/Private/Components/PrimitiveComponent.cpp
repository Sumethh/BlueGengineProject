#include "Components/PrimitiveComponent.h"
#include "Core/World.h"
#include "Core/Actor.h"
#include "Core/Scene.h"
#include "Components/MaterialComponent.h"
#include "Graphics/Material.h"
#include "Graphics/EImageFormat.h"

PrimitiveComponent::PrimitiveComponent(Actor* aOwner) : ActorComponent(aOwner),
				   mFullScreenLayer(EFullScreenLayer::Game),
				   mViewportLayer(EViewportLayer::World)
{
	GetOwner()->GetWorld()->RegisterPrimitiveComponent(this);
	SetParent(aOwner);
}

PrimitiveComponent::~PrimitiveComponent()
{
	Actor* owner = GetOwner();
	Scene* scene = (Scene*)owner->GetWorld();
	scene->DeregisterPimitiveComponent(this);
}

Material* PrimitiveComponent::GetMaterial()
{
	if (!mMaterialComponent)
	{
		mMaterialComponent = GetOwner()->GetComponent<MaterialComponent>();

		if (!mMaterialComponent)
		{
			mMaterialComponent = GetOwner()->AddComponent<MaterialComponent>();
		}
	}

	return mMaterialComponent->GetMaterial();
}

bool PrimitiveComponent::IsTranslucent()
{
	return GetMaterial()->HasAlpha();
}

uint64 PrimitiveComponent::GetRenderID(const Transform& aInverseCameraTransform)
{
	uint64 mReturningID = 0;

	return mReturningID;
}

glm::mat4 PrimitiveComponent::GetWorldMatrix()
{
	return GetOwner()->GetWorldMatrix();
}