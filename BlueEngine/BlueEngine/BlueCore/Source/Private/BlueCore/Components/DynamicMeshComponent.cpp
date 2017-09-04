#include "BlueCore/Components/DynamicMeshComponent.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Components/MaterialComponent.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Renderers/IRenderer.h"
#include "BlueCore/Managers/MeshManager.h"
#include <limits>
#include "BlueCore/Core/Vertex.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Helpers/MathHelpers.h"

namespace Blue
{
	DynamicMeshComponent::DynamicMeshComponent(Actor* aOwner) : PrimitiveComponent(aOwner)
	{
		SetMesh(MeshManager::GI()->GetMeshAsync("sphere", std::bind(&DynamicMeshComponent::SetMesh, this, std::placeholders::_1)));
	}

	DynamicMeshComponent::~DynamicMeshComponent()
	{

	}

	void DynamicMeshComponent::BeginPlay()
	{
		mMaterialComponent = GetOwner()->GetComponent<MaterialComponent>();

		if (!mMaterialComponent)
		{
			BlueAssert(false);
		}

		if (mMesh)
		{
			CalculateComponentBounds();
		}
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

		center = MathHelpers::RoundIfLowerThanEpsilon(center);

		glm::vec3 halfExtents;
		halfExtents.x = glm::abs(maxX - minX) / 2.0f;
		halfExtents.y = glm::abs(maxY - minY) / 2.0f;
		halfExtents.z = glm::abs(maxZ - minZ) / 2.0f;

		halfExtents = MathHelpers::RoundIfLowerThanEpsilon(halfExtents);

		mComponentBounds.halfExtents = halfExtents;
		mComponentBounds.position = center;
	}

	void DynamicMeshComponent::SubmitGeometry(IRenderer* aRenderer)
	{
		aRenderer->SetActiveMaterial(GetMaterial());
		aRenderer->SubmitGeometry(mMesh, GetWorldMatrix());
	}

	void DynamicMeshComponent::SetMesh(Mesh* aMesh)
	{
		mMesh = aMesh;
		SetBoundsFlagDirty();
	}
}