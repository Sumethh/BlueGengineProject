#pragma once
#include "Components/TransformComponent.h"
#include "Helpers/MathHelpers.h"
#include "Serialization/ArchiveObject.h"


#include <glm/gtx/matrix_decompose.hpp>
namespace BlueCore
{

	TransformComponent::TransformComponent(Actor* aOwner) :
	ActorComponent(aOwner, EComponentType::ETransformComponent),
				   mTransformFlags(0)
	{
	}

	TransformComponent::~TransformComponent()
	{

	}

	void TransformComponent::PreRender()
	{

	}

	void TransformComponent::OnSerialize(ArchiveObject* const aArchiveObject) const
	{

		ActorComponent::OnSerialize(aArchiveObject);
		aArchiveObject->Archive("Position", mTransform.position);
		aArchiveObject->Archive("Rotation", mTransform.rotation);
		aArchiveObject->Archive("Scale", mTransform.scale);
	}

	void TransformComponent::OnDeserialize(ArchiveObject* const aArchiveObject)
	{

	}

	BlueCore::Transform TransformComponent::GetWorldSpaceTransform()
	{
		glm::mat4 worldMat = GetWorldMatrix();
		Transform worldTrans;
		glm::vec3 skew;
		glm::vec4 persepective;
		glm::decompose(worldMat, worldTrans.scale, worldTrans.rotation, worldTrans.position, skew, persepective);
		return worldTrans;
	}

	void TransformComponent::SetParent(TransformComponent* aComp)
	{
		if (aComp)
		{
			//Need to calculate new localMatrix
			mLocalMatrix =  MathHelpers::ConvertToLocalSpace(GetWorldMatrix(), aComp->GetWorldMatrix());
			mParent = aComp;
			aComp->mChildren.push_back(this);
		}
		else
		{
			if (IsWorldMatrixDirty())
			{
				GetWorldMatrix();
			}

			mParent = nullptr;
		}
	}

	void TransformComponent::CalculateLocalMatrix()
	{
		glm::mat4 mat;
		mat = mTransform.MakeMat4();
		mLocalMatrix = mat;
		ResetLocalTransformDirtyFlag();
	}

	void TransformComponent::SetWorldTransformDirtyFlag()
	{
		mTransformFlags |= ETransformFlags::EWorldTransformDirty;

		for (auto child : mChildren)
		{
			child->SetWorldTransformDirtyFlag();
		}
	}

}