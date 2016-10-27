#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../GlmTransformationInclude.h"
#include "../Defines.h"
#include "ActorComponent.h"
#include <vector>
namespace BlueGengine
{

	struct Transform
	{
		Transform() :  position(0, 0, 0), scale(1, 1, 1) {}
		glm::vec3 position;
		glm::vec3 scale;
		glm::quat rotation;
	};

	class TransformComponent : public ActorComponent
	{
		enum ETransformFlags
		{
			ELocalTransformDirty = BlueBit(0),
			EWorldTransformDirty = BlueBit(1)
		};
		public:
		TransformComponent(Actor* a_owner);
		~TransformComponent();

		virtual void PreRender() override;

		Transform GetWorldSpaceTransform();
		//Returns Local space transform
		inline Transform GetTransform()const { return m_transform; }
		//Sets local space transform
		inline void SetTransform(Transform& a_transform)
		{
			m_transform = a_transform;
			SetLocalTransformDirtyFlag();
			SetWorldTransformDirtyFlag();
		}

		glm::mat4 inline GetLocalSpaceMatrix()
		{
			if (IsLocalTransformDirty())
			{
				CalculateLocalMatrix();
			}

			return m_localMatrix;
		}

		glm::mat4 inline GetWorldMatrix()
		{
			if (!m_parent)
			{
				//Local space is world space if there is no parent
				return GetLocalSpaceMatrix();
			}
			else
			{
				if (IsWorldMatrixDirty())
				{
					return  m_worldMatrix = m_parent->GetWorldMatrix() * GetLocalSpaceMatrix();
				}

				return m_worldMatrix;
			}
		}

		void SetParent(TransformComponent* a_comp);

		inline bool IsLocalTransformDirty() const { return (m_transformFlags & ETransformFlags::ELocalTransformDirty) > 0; }
		inline bool IsWorldMatrixDirty() const { return (m_transformFlags & ETransformFlags::EWorldTransformDirty) > 0; }

		glm::vec3 GetForwardVector() { return glm::normalize(m_transform.rotation * glm::vec3(0.0f, 0.0f, 1.0f)); }
		glm::vec3 GetRightVector() {   return glm::normalize(m_transform.rotation * glm::vec3(1.0f, 0.0f, 0.0f));}
		glm::vec3 GetUpVector() {      return glm::normalize(m_transform.rotation * glm::vec3(0.0f, 1.0f, 0.0f)); }

		private:

		inline void ResetLocalTransformDirtyFlag() { m_transformFlags &= ~ETransformFlags::ELocalTransformDirty; }
		inline void SetLocalTransformDirtyFlag() { m_transformFlags |= ETransformFlags::ELocalTransformDirty; }

		void SetWorldTransformDirtyFlag();
		inline void ResetWorldTransformDirtyFlag() { m_transformFlags &= ~ETransformFlags::EWorldTransformDirty; }

		void CalculateLocalMatrix();
		TransformComponent* m_parent;
		std::vector<TransformComponent*> m_children;
		uint32 m_transformFlags;
		Transform m_transform;
		glm::mat4 m_localMatrix;
		glm::mat4 m_worldMatrix;
	};
}