#include "FirstPersonComponent.h"
#include "../Actor.h"
#include "TransformComponent.h"
#include "../Input.h"
#include "../Helpers/MathHelpers.h"
#include "../imgui/imgui.h"
#include <glm/gtc/constants.hpp>
#include "../ApplicationWindow.h"
BlueGengine::FirstPersonComponent::FirstPersonComponent(Actor* a_owner) : ActorComponent(a_owner, EComponentType::EFirstPersonComponent)
{
}
void BlueGengine::FirstPersonComponent::Update(float a_dt)
{
	Transform trans = GetOwner()->GetTransformComponent()->GetTransform();
	glm::vec3 forward = GetOwner()->GetTransformComponent()->GetForwardVector();
	glm::vec3 right = GetOwner()->GetTransformComponent()->GetRightVector();
	glm::vec3 up = GetOwner()->GetTransformComponent()->GetUpVector();
	glm::vec3 movement = glm::vec3(m_moveSpeed * a_dt);

	if (Input::GetKeyDown(Input::Key::W))
	{
		trans.position += forward * movement;
	}
	else if (Input::GetKeyDown(Input::Key::S))
	{
		trans.position -= forward * movement;
	}

	if (Input::GetKeyDown(Input::Key::D))
	{
		trans.position += right * movement;
	}
	else if (Input::GetKeyDown(Input::Key::A))
	{
		trans.position -= right * movement;
	}

	if (Input::GetKeyDown(Input::Key::E))
	{
		trans.position += up * movement;
	}
	else if (Input::GetKeyDown(Input::Key::Q))
	{
		trans.position -= up * movement;
	}
	GetOwner()->GetTransformComponent()->SetTransform(trans);
}
