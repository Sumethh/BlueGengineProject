#include "FirstPersonComponent.h"
#include "../Actor.h"
#include "TransformComponent.h"
#include "../Input.h"
#include "../Helpers/MathHelpers.h"
#include "../imgui/imgui.h"
#include <glm/gtc/constants.hpp>
#include "../ApplicationWindow.h"
BlueGengine::FirstPersonComponent::FirstPersonComponent(Actor* aOwner) : ActorComponent(aOwner, EComponentType::EFirstPersonComponent)
{

}

void BlueGengine::FirstPersonComponent::BeginPlay()
{
}

void BlueGengine::FirstPersonComponent::Update(float aDt)
{
	Transform trans = GetOwner()->GetTransformComponent()->GetTransform();
	glm::vec3 forward = GetOwner()->GetTransformComponent()->GetForwardVector();
	glm::vec3 right = GetOwner()->GetTransformComponent()->GetRightVector();
	glm::vec3 up = GetOwner()->GetTransformComponent()->GetUpVector();
	glm::vec3 movement = glm::vec3(mMoveSpeed * aDt);

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

	glm::vec3 euler = QuatToEuler(trans.rotation);
	glm::quat resultingQuat;

	if (Input::GetMouseButtonDown(1))
	{
		glm::vec2 mouseMove;
		Input::GetMouseMove(mouseMove.x, mouseMove.y);

		if (glm::length(mouseMove) < 10.0f && glm::length(mouseMove) > 0.0f)
		{
			euler.x += mouseMove.y * mLookSpeed * aDt;
			euler.y += mouseMove.x * mLookSpeed * aDt;
		}

	}

	trans.rotation = QuatFromEuler(euler);
	ImGui::LabelText("Camera Rot", "%f, %f, %f", euler.x, euler.y, euler.z);
	GetOwner()->GetTransformComponent()->SetTransform(trans);
}
