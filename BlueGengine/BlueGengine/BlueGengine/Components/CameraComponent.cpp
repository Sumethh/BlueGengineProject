#include "CameraComponent.h"
#include "../Actor.h"
#include "TransformComponent.h"
#include "../GlmTransformationInclude.h"
#include "../Defines.h"
#include "../RendererInterface.h"
#include "../Imgui/imgui.h"
#include "../Helpers/MathHelpers.h"
namespace BlueGengine
{
	CameraComponent::CameraComponent(Actor* a_owner) : ActorComponent(a_owner, EComponentType::ECameraComponent)
	{
		m_projectionMatrix = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
	}

	CameraComponent::~CameraComponent()
	{

	}

	void CameraComponent::PreRender()
	{
		TransformComponent* transformComp = GetOwner()->GetTransformComponent();
		Transform trans = transformComp->GetTransform();
		glm::vec3 rotation = QuatToRadians(trans.rotation);
		ImGui::LabelText("Camera Position", "%f, %f, %f", trans.position.x, trans.position.y, trans.position.z);


		glm::vec3 forward = transformComp->GetForwardVector();
		glm::vec3 up = transformComp->GetUpVector();
		ImGui::LabelText("Up", "%f, %f, %f", up.x, up.y, up.z);
		ImGui::LabelText("Forward", "%f, %f, %f", forward.x, forward.y, forward.z);

		m_viewMatrix = glm::mat4();
		m_viewMatrix = glm::lookAt(trans.position, trans.position + forward, up);
		ImGui::LabelText("ViewPos", "%f, %f, %f", m_viewMatrix[3][0]  , m_viewMatrix[3][1], m_viewMatrix[3][2]);
	}

	void CameraComponent::Render(IRenderer* a_renderer)
	{
		a_renderer->SubmitCamera(this);
	}

}