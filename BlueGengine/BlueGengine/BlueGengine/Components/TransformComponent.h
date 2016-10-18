#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../GlmTransformationInclude.h"
#include "../Defines.h"
#include "ActorComponent.h"
namespace BlueGengine
{

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 scale;
		//Rotation in radians
		glm::quat rotation;
	};

	class TransformComponent : public ActorComponent
	{
		enum ETransformFlags
		{
			ETransformDirty = BlueBit(0)
		};
		public:
		TransformComponent(Actor* a_owner);
		~TransformComponent();

		virtual void PreRender() override;

		inline Transform GetTransform()const { return m_transform; }
		inline void SetTransform(Transform& a_transform) { m_transform = a_transform; SetTransformDirtyFlag(); }

		glm::mat4 inline GetLocalSpaceMatrix()
		{
			if (IsTransformDirty())
			{
				CalculateLocalMatrix();
			}
			return m_localMatrix;
		}

		glm::mat4 inline GetWorldMatrix()
		{
			if (!m_parent)
			{
				//Local space is world space if i dont have a parent
				return GetLocalSpaceMatrix();
			}
			else
			{
				return m_parent->GetLocalSpaceMatrix() * GetLocalSpaceMatrix();
			}
		}

		inline bool IsTransformDirty() const { return (m_transformFlags & ETransformFlags::ETransformDirty) > 0; }


		private:
		inline void ResetTransformDirtyFlag() { m_transformFlags &= ~ETransformFlags::ETransformDirty; }
		inline void SetTransformDirtyFlag() { m_transformFlags |= ETransformFlags::ETransformDirty; }

		void CalculateLocalMatrix();
		TransformComponent* m_parent;
		uint32 m_transformFlags;
		Transform m_transform;
		glm::mat4 m_localMatrix;
	};
}