#include "Components/CameraComponent.h"
#include "Core/Actor.h"
#include "Components/TransformComponent.h"
#include "Core/GlmTransformationInclude.h"
#include "Core/Defines.h"
#include "Renderers/RendererInterface.h"
#include "Imgui/imgui.h"
#include "Helpers/MathHelpers.h"
namespace BlueCore
{
	CameraComponent* CameraComponent::mCurrentActiveCamera;
	CameraComponent::CameraComponent(Actor* aOwner) : ActorComponent(aOwner, EComponentType::ECameraComponent)
	{
		mProjectionMatrix = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
		SetActive();
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::BeginPlay()
	{
		ActorComponent::BeginPlay();
		auto t = GetOwner()->GetTransformComponent()->GetTransform();
		t.rotation = MathHelpers::QuatFromEuler(glm::vec3(0, 0, 0));
		GetOwner()->GetTransformComponent()->SetTransform(t);
	}

	void CameraComponent::PreRender()
	{
		TransformComponent* transformComp = GetOwner()->GetTransformComponent();
		Transform trans = transformComp->GetTransform();
		glm::vec3 rotation = MathHelpers::QuatToRadians(trans.rotation);
		ImGui::LabelText("Camera Position", "%f, %f, %f", trans.position.x, trans.position.y, trans.position.z);


		glm::vec3 forward = transformComp->GetForwardVector();
		glm::vec3 up = transformComp->GetUpVector();

		mViewMatrix = glm::mat4();
		mViewMatrix = glm::lookAt(trans.position, trans.position + forward, up);
	}

	void CameraComponent::Render(IRenderer* aRenderer)
	{
		aRenderer->SubmitCamera(this);
	}

}