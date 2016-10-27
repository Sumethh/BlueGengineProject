#pragma once
#include "TransformComponent.h"
#include "../Helpers/MathHelpers.h"
#include <glm/gtx/matrix_decompose.hpp>
namespace BlueGengine
{

	TransformComponent::TransformComponent(Actor* a_owner) :
	ActorComponent(a_owner, EComponentType::ETransformComponent),
				   m_transformFlags(0)
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

	void TransformComponent::SetParent(TransformComponent* a_comp)
	{
		if (a_comp)
		{
			//Need to calculate new localMatrix
			m_localMatrix =  ConvertToLocalSpace(GetWorldMatrix(), a_comp->GetWorldMatrix());
			m_parent = a_comp;
		}
		else
		{
			if (IsWorldMatrixDirty())
			{
				GetWorldMatrix();
			}

			m_parent = nullptr;
		}
	}

	void TransformComponent::CalculateLocalMatrix()
	{
		glm::mat4 mat;
		mat = glm::translate(mat, m_transform.position);
		mat = glm::scale(mat, m_transform.scale);
		glm::mat4 rotQuat(glm::mat4_cast(m_transform.rotation));
		mat *= rotQuat;
		m_localMatrix = mat;
		ResetLocalTransformDirtyFlag();
	}

	void TransformComponent::SetWorldTransformDirtyFlag()
	{
		m_transformFlags |= ETransformFlags::EWorldTransformDirty;

		for (auto child : m_children)
		{
			child->SetWorldTransformDirtyFlag();
		}
	}

}