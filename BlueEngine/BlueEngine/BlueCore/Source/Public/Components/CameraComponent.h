#pragma once
#include "ActorComponent.h"
#include <glm/glm.hpp>
namespace BlueCore
{
	class IRenderer;
	class CameraComponent : public ActorComponent
	{
		public:
		CameraComponent(Actor* aOwner);
		~CameraComponent();

		virtual void BeginPlay();

		virtual void PreRender() override;
		virtual void Render(IRenderer* aRenderer) override;

		inline void SetProjectionMatrix(glm::mat4 aNewProjectionMatrix) { mProjectionMatrix = aNewProjectionMatrix; }

		glm::mat4 GetProjectionMatrix() const { return mProjectionMatrix; }
		glm::mat4 GetViewMatrix()const { return mViewMatrix; }

		inline void SetActive() { mCurrentActiveCamera = this; }
		static CameraComponent* GetActiveCamera() { return mCurrentActiveCamera; }
		private:
		static CameraComponent* mCurrentActiveCamera;

		glm::mat4 mProjectionMatrix;
		glm::mat4 mViewMatrix;
	};
}