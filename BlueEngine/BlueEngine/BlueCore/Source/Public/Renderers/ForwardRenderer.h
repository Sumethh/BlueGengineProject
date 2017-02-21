#pragma once
#include "RendererInterface.h"
#include <map>
#include <vector>
#include "Core/Types.h"
#include "Core/GlmTransformationInclude.h"


struct Transform;
class Light;
class   ForwardRenderer : public IRenderer
{
	public:
	ForwardRenderer();
	~ForwardRenderer();

	void SubmitMesh(Mesh* aMesh, Material* aMaterial, Transform aTransform) override;
	void SubmitCamera(CameraComponent* aCamera) override;
	void Flush()override ;
	private:
};

