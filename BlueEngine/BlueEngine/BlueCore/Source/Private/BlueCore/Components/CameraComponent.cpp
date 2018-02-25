#include "BlueCore/Components/CameraComponent.h"
#include "BlueCore/Core/Actor.h"
#include "BlueCore/Core/Transformable.h"
#include "BlueCore/Core/World.h"
#include "BlueCore/Core/GlmTransformationInclude.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Renderers/IRenderer.h"
#include "BlueCore/Helpers/MathHelpers.h"
#include "BlueCore/Messaging/WindowResizeMessage.h"
#include "BlueCore/Core/ApplicationWindow.h"

namespace Blue
{
	IMPLEMENT_ACTOR_COMPONENT_BASE_FUNCTIONALITY(CameraComponent);

	CameraComponent::CameraComponent(Actor* aOwner) : ActorComponent(aOwner)
	{

	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::PostConstruction()
	{
		ApplicationWindow* window = ApplicationWindow::GetCurrentWindow();
		mProjectionMatrix = glm::perspective(45.0f, static_cast<float>(window->GetWindowWidth()) / static_cast<float>(window->GetWindowHeight()), 0.1f, 1000.0f);
		mViewport.SetDimensions(glm::vec2(1, 1));
		mViewport.SetPosition(glm::vec2(0, 0));

		GetOwner()->GetWorld()->RegisterCamera(this);
		Message<WindowResizeMessage>::Listen(this, &CameraComponent::OnWindowResize);
	}

	void CameraComponent::BeginPlay()
	{
		ActorComponent::BeginPlay();
	}

	glm::mat4 CameraComponent::GetProjectionMatrix()
	{
		return mProjectionMatrix;
	}

	glm::mat4 CameraComponent::GetViewMatrix()
	{
		return GetOwner()->GetWorldMatrix();
	}

	void CameraComponent::CaptureData(CapturedCameraData& aData)
	{
		aData.cameraTransform = GetOwner()->GetTransform();
		aData.projectionMatrix = GetProjectionMatrix();
		aData.viewMatrix = GetViewMatrix();
	}

	void CameraComponent::OnWindowResize(WindowResizeMessage* aMessage)
	{
		mProjectionMatrix = glm::perspective(90.0f, static_cast<float>(aMessage->windowWidth) / static_cast<float>(aMessage->windowHeight), 0.1f, 1000.0f);
	}
}