#include "DynamicMeshComponent.h"
#include "../Actor.h"
#include "MaterialComponent.h"
#include "TransformComponent.h"
#include "../Renderers/RendererInterface.h"
#include "../MeshManager.h"
namespace BlueGengine
{

	DynamicMeshComponent::DynamicMeshComponent(Actor* aOwner) : ActorComponent(aOwner, EComponentType::EMeshComponent)
	{
		mMesh = MeshManager::GI()->GetMeshAsync("cube", std::bind(&DynamicMeshComponent::SetMesh, this, std::placeholders::_1));
	}

	DynamicMeshComponent::~DynamicMeshComponent()
	{

	}

	void DynamicMeshComponent::BeginPlay()
	{
		mTransformComponent = GetOwner()->GetTransformComponent();
		mMaterialComponent = (MaterialComponent*)GetOwner()->GetComponent(EComponentType::EMaterialComponent);

		if (!mMaterialComponent)
		{
			Actor* owner = GetOwner();
			owner->AddComponent(EComponentType::EMaterialComponent);
		}
	}

	void DynamicMeshComponent::PreRender()
	{
	}

	void DynamicMeshComponent::Render(IRenderer* aRenderer)
	{

		aRenderer->SubmitMesh(mMesh, mMaterialComponent->GetMaterial(), mTransformComponent->GetWorldSpaceTransform());

	}

}