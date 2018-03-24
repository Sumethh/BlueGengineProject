#include "BlueCore/Components/PrimitiveComponent.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Core/Scene.h"
#include "BlueCore/Components/MaterialComponent.h"
#include "BlueCore/Graphics/Material.h"

namespace Blue
{
	PrimitiveComponent::PrimitiveComponent(Actor* aOwner) : ActorComponent(aOwner),
		mFullScreenLayer(EFullScreenLayer::Game),
		mViewportLayer(EViewportLayer::World),
		mMaterialComponent(nullptr)
	{
	}

	PrimitiveComponent::~PrimitiveComponent()
	{

	}

	void PrimitiveComponent::PostConstruction()
	{
		GetOwner()->GetWorld()->RegisterPrimitiveComponent(this);
		SetParent(GetOwner());
	}

	void PrimitiveComponent::PreDestruction()
	{
		Actor* owner = GetOwner();
		Scene* scene = static_cast<Scene*>(owner->GetWorld());
		scene->DeregisterPimitiveComponent(this);
		mMaterialComponent = nullptr;
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
		(void)aInverseCameraTransform;
		uint64 mReturningID = 0;

		return mReturningID;
	}
}