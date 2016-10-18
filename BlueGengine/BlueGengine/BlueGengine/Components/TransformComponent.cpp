#pragma once
#include "TransformComponent.h"

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

	void TransformComponent::CalculateLocalMatrix()
	{
		glm::mat4 mat;
		mat = glm::translate(mat, m_transform.position);
		mat = glm::scale(mat, m_transform.scale);
		glm::mat4 rotQuat(glm::mat4_cast(m_transform.rotation));
		mat *= rotQuat;
		m_localMatrix = mat;
		ResetTransformDirtyFlag();
	}
}