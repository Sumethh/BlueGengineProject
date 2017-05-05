#pragma once
#include "ActorComponent.h"
#include "Graphics/ViewPort.h"
#include <glm/glm.hpp>

class IRenderer;
struct WindowResizeMessage;
class   CameraComponent: public ActorComponent
{
public:
	CameraComponent(Actor* aOwner);
	~CameraComponent();

	uint64 ID() { return CompileHash("CameraComponent"); }

	virtual void BeginPlay();

	inline void SetProjectionMatrix(glm::mat4 aNewProjectionMatrix) { mProjectionMatrix = aNewProjectionMatrix; }

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

private:
	void OnWindowResize(WindowResizeMessage* aMessage);
	Viewport mViewport;
	glm::mat4 mProjectionMatrix;
	glm::mat4 mViewMatrix;

};