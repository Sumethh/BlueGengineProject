#pragma once
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Serialization/ArchiveObject.h"



namespace Blue
{
	Transformable::Transformable() :
		mTransformFlags(0)
	{
	}

	Transformable::~Transformable()
	{

	}

	void Transformable::OnSerialize(ArchiveObject* const aArchiveObject) const
	{
		aArchiveObject->Archive("Position", mTransform.position);
		aArchiveObject->Archive("Rotation", mTransform.rotation);
		aArchiveObject->Archive("Scale", mTransform.scale);
	}

	void Transformable::OnDeserialize(ArchiveObject* const aArchiveObject)
	{

	}

	Transform Transformable::GetWorldSpaceTransform()
	{
		glm::mat4 worldMat = GetWorldMatrix();
		Transform worldTrans;
		glm::vec3 skew;
		glm::vec4 persepective;
		glm::decompose(worldMat, worldTrans.scale, worldTrans.rotation, worldTrans.position, skew, persepective);
		return worldTrans;
	}

	void Transformable::SetParent(Transformable* aComp)
	{
		if (aComp)
		{
			//Need to calculate new localMatrix
			mLocalMatrix = MathHelpers::ConvertToLocalSpace(GetWorldMatrix(), aComp->GetWorldMatrix());
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

	void Transformable::CalculateLocalMatrix()
	{
		glm::mat4 mat;
		mat = mTransform.MakeMat4();
		mLocalMatrix = mat;
		ResetLocalTransformDirtyFlag();
	}

	void Transformable::SetWorldTransformDirtyFlag()
	{
		mTransformFlags |= ETransformFlags::EWorldTransformDirty;

		for (auto child : mChildren)
		{
			child->SetWorldTransformDirtyFlag();
		}
	}
}