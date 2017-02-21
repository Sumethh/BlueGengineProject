#include "Components/FirstPersonComponent.h"
#include "Core/Actor.h"
#include "Components/TransformComponent.h"
#include "Input/Input.h"
#include "Helpers/MathHelpers.h"

#include "Core/ApplicationWindow.h"
#include "Core/Log.h"
#include <glm/gtc/constants.hpp>
FirstPersonComponent::FirstPersonComponent(Actor* aOwner) : ActorComponent(aOwner)
{

}

void FirstPersonComponent::BeginPlay()
{
}

void FirstPersonComponent::Update(float aDt)
{
	Transform trans = GetOwner()->GetTransformComponent()->GetTransform();
	glm::vec3 forward = GetOwner()->GetTransformComponent()->GetForwardVector();
	glm::vec3 right = GetOwner()->GetTransformComponent()->GetRightVector();
	glm::vec3 up = GetOwner()->GetTransformComponent()->GetUpVector();
	glm::vec3 movement = glm::vec3(mMoveSpeed * aDt);

	if (!Input::IsKeyboardCaptured())
	{
		if (Input::GetKeyDown(Input::Key::LEFT_SHIFT))
		{
			movement *= 5.0f;
		}

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
	}

	glm::vec3 euler = MathHelpers::QuatToEuler(trans.rotation);
	glm::quat resultingQuat;

	if (Input::GetMouseButtonDown(1) && !Input::isMouseOverUI())
	{
		glm::vec2 mouseMove;
		Input::GetMouseMove(mouseMove.x, mouseMove.y);

		if (glm::length(mouseMove))
		{
			euler.x += mouseMove.y * (mLookSpeed * aDt);
			euler.y += mouseMove.x * (mLookSpeed * aDt);
		}

	}

	trans.rotation = MathHelpers::QuatFromEuler(euler);
	GetOwner()->GetTransformComponent()->SetTransform(trans);
}
