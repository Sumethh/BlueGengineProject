#pragma once
#include <unordered_map>
#include "Core/Transformable.h"

class Mesh;
class Material;
class CameraComponent;
class IRenderer
{
	public:
	virtual void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) = 0;
	virtual void SetActiveCamera(CameraComponent* aCamera) = 0;
	virtual void SetActiveMaterial(Material* aMaterial) = 0;
	virtual void End() = 0;
};
