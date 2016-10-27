#pragma once
#include "ActorComponent.h"
#include <glm/glm.hpp>
namespace BlueGengine
{
	class IRenderer;
	class CameraComponent : public ActorComponent
	{
		public:
		CameraComponent(Actor* a_owner);
		~CameraComponent();


		virtual void PreRender() override;
		virtual void Render(IRenderer* a_renderer) override;

		inline void SetProjectionMatrix(glm::mat4 a_newProjectionMatrix) { m_projectionMatrix = a_newProjectionMatrix; }

		glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }
		glm::mat4 GetViewMatrix()const { return m_viewMatrix; }
		private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
	};
}