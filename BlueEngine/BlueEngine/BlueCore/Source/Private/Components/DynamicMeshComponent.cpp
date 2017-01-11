#include "Components/DynamicMeshComponent.h"
#include "Core/Actor.h"
#include "Components/MaterialComponent.h"
#include "Components/TransformComponent.h"
#include "Renderers/RendererInterface.h"
#include "Managers/MeshManager.h"
#include <limits>
#include "Core/Vertex.h"
#include "Graphics/Mesh.h"
#include "Helpers/MathHelpers.h"
namespace BlueCore
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
			mMaterialComponent = (MaterialComponent*)owner->AddComponent(EComponentType::EMaterialComponent);
		}

		CalculateComponentBounds();
	}

	void DynamicMeshComponent::PreRender()
	{
	}

	void DynamicMeshComponent::Render(IRenderer* aRenderer)
	{

		aRenderer->SubmitMesh(mMesh, mMaterialComponent->GetMaterial(), mTransformComponent->GetWorldSpaceTransform());

	}

	void DynamicMeshComponent::CalculateComponentBounds()
	{
		Vertex* vertices = mMesh->GetVertices();
		uint32 vertCount = mMesh->GetVerticeCount();

		float maxX = std::numeric_limits<float>::min();
		float maxY = std::numeric_limits<float>::min();
		float maxZ = std::numeric_limits<float>::min();

		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float minZ = std::numeric_limits<float>::max();

		for (uint32 i = 0; i < vertCount; ++i)
		{
			Vertex vert = vertices[i];
			maxX = glm::max(maxX, vert.position.x);
			minX = glm::min(minX, vert.position.x);

			maxY = glm::max(maxX, vert.position.y);
			minY = glm::min(minX, vert.position.y);

			maxZ = glm::max(maxX, vert.position.z);
			minZ = glm::min(minX, vert.position.z);
		}

		glm::vec3 center;
		center.x = maxX + minX;
		center.y = maxY + minY;
		center.z = maxZ + minZ;

		MathHelpers::RoundIfLowerThanEpsilon(center);

		glm::vec3 halfExtents;
		halfExtents.x = glm::abs(maxX - minX) / 2.0f;
		halfExtents.y = glm::abs(maxY - minY) / 2.0f;
		halfExtents.z = glm::abs(maxZ - minZ) / 2.0f;

		MathHelpers::RoundIfLowerThanEpsilon(halfExtents);

		int t = 0;
	}

}