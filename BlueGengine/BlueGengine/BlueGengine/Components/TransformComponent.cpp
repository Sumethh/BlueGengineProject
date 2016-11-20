#pragma once
#include "TransformComponent.h"
#include "../Helpers/MathHelpers.h"
#include <glm/gtx/matrix_decompose.hpp>
namespace BlueGengine
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

	BlueGengine::Transform TransformComponent::GetWorldSpaceTransform()
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
			mLocalMatrix =  ConvertToLocalSpace(GetWorldMatrix(), aComp->GetWorldMatrix());
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