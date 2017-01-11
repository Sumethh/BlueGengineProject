#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Core/GlmTransformationInclude.h"
#include "Core/Defines.h"
#include "ActorComponent.h"
#include <vector>
namespace BlueCore
{

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
	};

	class TransformComponent : public ActorComponent
	{
		enum ETransformFlags
		{
			ELocalTransformDirty = BlueBit(0),
			EWorldTransformDirty = BlueBit(1)
		};
		public:
		TransformComponent(Actor* aOwner);
		~TransformComponent();

		virtual void PreRender() override;

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

		glm::mat4 inline GetLocalSpaceMatrix()
		{
			if (IsLocalTransformDirty())
			{
				CalculateLocalMatrix();
			}

			return mLocalMatrix;
		}

		glm::mat4 inline GetWorldMatrix()
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

		void SetParent(TransformComponent* aComp);

		inline bool IsLocalTransformDirty() const { return (mTransformFlags & ETransformFlags::ELocalTransformDirty) > 0; }
		inline bool IsWorldMatrixDirty() const { return (mTransformFlags & ETransformFlags::EWorldTransformDirty) > 0; }

		glm::vec3 GetForwardVector() {return glm::normalize((mTransform.rotation) * glm::vec3(0.0f, 0.0f, 1.0f)); }
		glm::vec3 GetRightVector()   {return glm::normalize((mTransform.rotation) * glm::vec3(1.0f, 0.0f, 0.0f));}
		glm::vec3 GetUpVector()      {return glm::normalize((mTransform.rotation) * glm::vec3(0.0f, 1.0f, 0.0f)); }

		private:

		inline void ResetLocalTransformDirtyFlag() { mTransformFlags &= ~ETransformFlags::ELocalTransformDirty; }
		inline void SetLocalTransformDirtyFlag() { mTransformFlags |= ETransformFlags::ELocalTransformDirty; }

		void SetWorldTransformDirtyFlag();
		inline void ResetWorldTransformDirtyFlag() { mTransformFlags &= ~ETransformFlags::EWorldTransformDirty; }

		void CalculateLocalMatrix();
		TransformComponent* mParent;
		std::vector<TransformComponent*> mChildren;
		uint32 mTransformFlags;
		Transform mTransform;
		glm::mat4 mLocalMatrix;
		glm::mat4 mWorldMatrix;
	};
}