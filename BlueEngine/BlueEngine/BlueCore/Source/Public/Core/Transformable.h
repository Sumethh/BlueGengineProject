#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Core/Defines.h"
#include "Core/GlmTransformationInclude.h"
#include "Serialization/ISerializable.h"
#include "Core/Transformable.h"


#include <vector>
#include <glm/gtx/matrix_decompose.hpp>

struct Transform
{
	Transform() : position(0, 0, 0), scale(1, 1, 1) {}
	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotation;
	glm::mat4 MakeMat4()
	{
		glm::mat4 mat;
		mat = glm::translate(mat, position);
		mat = glm::scale(mat, scale);
		mat *= glm::mat4_cast(rotation);
		return mat;
	}
	void FromMatrix(glm::mat4& aMat)
	{
		glm::vec3 skew;
		glm::vec4 persepective;
		glm::decompose(aMat, scale, rotation, position, skew, persepective);
	}
};

class Transformable : ISerializable
{
	enum ETransformFlags
	{
		ELocalTransformDirty = BlueBit(0),
		EWorldTransformDirty = BlueBit(1)
	};
	public:
	Transformable();
	~Transformable();

	virtual void OnSerialize(ArchiveObject* const aArchiveObject) const override;
	virtual void OnDeserialize(ArchiveObject* const aArchiveObject) override;

	Transform GetWorldSpaceTransform();

	//Returns Local space transform
	inline Transform GetTransform()const { return mTransform; }
	//Sets local space transform
	inline void SetTransform(Transform& aTransform)
	{
		mTransform = aTransform;
		SetLocalTransformDirtyFlag();
		SetWorldTransformDirtyFlag();
	}

	inline glm::mat4 GetLocalSpaceMatrix()
	{
		if (IsLocalTransformDirty())
		{
			CalculateLocalMatrix();
		}

		return mLocalMatrix;
	}
	inline glm::mat4 GetWorldMatrix()
	{
		if (!mParent)
		{
			//Local space is world space if there is no parent
			return GetLocalSpaceMatrix();
		}
		else
		{
			if (IsWorldMatrixDirty())
			{
				ResetWorldTransformDirtyFlag();
				return  mWorldMatrix = mParent->GetWorldMatrix() * GetLocalSpaceMatrix();
			}

			return mWorldMatrix;
		}
	}

	void SetParent(Transformable* aComp);
	inline Transformable* GetParent() { return mParent; }
	inline std::vector<Transformable*>& GetChildren() { return mChildren; }

	inline bool IsLocalTransformDirty() const { return (mTransformFlags & ETransformFlags::ELocalTransformDirty) > 0; }
	inline bool IsWorldMatrixDirty() const { return (mTransformFlags & ETransformFlags::EWorldTransformDirty) > 0; }

	inline glm::vec3 GetForwardVector() {return glm::normalize((mTransform.rotation) * glm::vec3(0.0f, 0.0f, 1.0f)); }
	inline glm::vec3 GetRightVector()   {return glm::normalize((mTransform.rotation) * glm::vec3(1.0f, 0.0f, 0.0f));}
	inline glm::vec3 GetUpVector()      {return glm::normalize((mTransform.rotation) * glm::vec3(0.0f, 1.0f, 0.0f)); }

	private:

	inline void ResetWorldTransformDirtyFlag() { mTransformFlags &= ~ETransformFlags::EWorldTransformDirty; }
	inline void ResetLocalTransformDirtyFlag() { mTransformFlags &= ~ETransformFlags::ELocalTransformDirty; }
	inline void SetLocalTransformDirtyFlag() { mTransformFlags |= ETransformFlags::ELocalTransformDirty; }

	void SetWorldTransformDirtyFlag();
	void CalculateLocalMatrix();

	Transformable* mParent;
	std::vector<Transformable*> mChildren;
	uint32 mTransformFlags;

	Transform mTransform;

	glm::mat4 mLocalMatrix;
	glm::mat4 mWorldMatrix;
};
