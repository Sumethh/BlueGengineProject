#pragma once
#include "IRenderer.h"
#include <map>
#include <vector>
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/GlmTransformationInclude.h"

namespace Blue
{
	struct Transform;
	struct SceneLighting;
	class Light;
	class Shader;
	class Material;
	class ForwardRenderer : public IRenderer
	{
	public:
		ForwardRenderer();
		~ForwardRenderer();

		void SubmitGeometry(CapturedPrimitiveData& aPrimitiveData);
		void SetActiveCamera(CapturedCameraData& aCamera) override;
		void SetActiveLighting(SceneLighting* aLighting) override;
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