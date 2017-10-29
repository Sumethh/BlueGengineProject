#pragma once
#include "ActorComponent.h"
#include "BlueCore/Graphics/ViewPort.h"
#include <glm/glm.hpp>

namespace Blue
{
	class IRenderer;
	struct WindowResizeMessage;
	class   CameraComponent : public ActorComponent
	{
	public:
		DEFINE_ACTOR_COMPONENT_BASE_FUNCTIONALITY();

		CameraComponent(Actor* aOwner);
		~CameraComponent();

		virtual void PostConstruction() override;
		virtual void BeginPlay();

		inline void SetProjectionMatrix(glm::mat4 aNewProjectionMatrix)
		{
			mProjectionMatrix = aNewProjectionMatrix;
		}

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

	private:
		void OnWindowResize(WindowResizeMessage* aMessage);
		Viewport mViewport;
		glm::mat4 mProjectionMatrix;

	};
}