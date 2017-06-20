#pragma once
#include "IRenderer.h"
#include <map>
#include <vector>
#include "Core/Types.h"
#include "Core/GlmTransformationInclude.h"

namespace Blue
{
	struct Transform;
	class Light;
	class Shader;
	class Material;
	class ForwardRenderer : public IRenderer
	{
	public:
		ForwardRenderer();
		~ForwardRenderer();

		void SubmitGeometry(Mesh* aMesh, glm::mat4 aTransform) override;
		void SetActiveCamera(CameraComponent* aCamera) override;
		void SetActiveMaterial(Material* aMaterial) override;

		void End() override;
	private:
		glm::mat4 mActiveProjectionMatrix;
		glm::mat4 mActiveViewMatrix;
		Material* mActiveMaterial;
		Shader* mCurrentShader;
		Mesh* mCurrentMesh;
		uint32 mModelLocation;
	};
}