#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Core/GlmTransformationInclude.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Renderers/IRenderer.h"
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Messaging/WindowResizeMessage.h"

namespace Blue
{
	CameraComponent::CameraComponent(Actor* aOwner) : ActorComponent(aOwner)
	{
		mProjectionMatrix = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
		mViewport.SetDimensions(glm::vec2(1, 1));
		mViewport.SetPosition(glm::vec2(0, 0));

		GetOwner()->GetWorld()->RegisterCamera(this);
		Message<WindowResizeMessage>::Listen(this, &CameraComponent::OnWindowResize);
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::BeginPlay()
	{
		ActorComponent::BeginPlay();
		auto t = GetOwner()->GetTransform();
		t.rotation = glm::quat(1, 0, 0, 0);
		GetOwner()->SetTransform(t);
	}

	glm::mat4 CameraComponent::GetProjectionMatrix()
	{
		return mProjectionMatrix;
	}

	glm::mat4 CameraComponent::GetViewMatrix()
	{
		return GetOwner()->GetWorldMatrix();
	}

	void CameraComponent::OnWindowResize(WindowResizeMessage* aMessage)
	{
		mProjectionMatrix = glm::perspective(45.0f, (float)aMessage->windowWidth / (float)aMessage->windowHeight, 0.1f, 1000.0f);
	}
}