#pragma once
#include <unordered_map>
#include "../Components/TransformComponent.h"

class Mesh;
class Material;
class CameraComponent;
class   IRenderer
{
	public:

	virtual void SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform) = 0;
	virtual void SubmitCamera(CameraComponent* aCamera) = 0;
	virtual void Flush() = 0;
};
