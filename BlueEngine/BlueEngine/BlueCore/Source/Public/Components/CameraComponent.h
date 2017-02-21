#pragma once
#include "ActorComponent.h"
#include "Graphics/ViewPort.h"
#include <glm/glm.hpp>

class IRenderer;
class   CameraComponent: public ActorComponent
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

	private:

	Viewport mViewport;
	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;

};