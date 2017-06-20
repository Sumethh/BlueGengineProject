#include "Managers/MaterialManager.h"
#include "Graphics/Material.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Shader.h"

namespace Blue
{
	void MaterialManager::CreateDefaultMaterials()
	{
		Material* defaultMaterial = CreateMaterial();
		Shader* shader = new Shader();
		shader->LoadShader("assets/shaders/glsl/Forward/Forward_Shaded.glslv", "assets/shaders/glsl/Forward/Forward_Shaded.glslf");
		int t = 0;
		Texture2D* tex = new Texture2D();
		tex->LoadTexture("Assets/Textures/Debug.png", EImageFormat::RGB, EPrecisionType::RGB_8Bit);
		defaultMaterial->SetShader(shader);
		defaultMaterial->SetTexture(tex);
		defaultMaterial->SetAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
		defaultMaterial->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		defaultMaterial->SetSpecularPower(0.1f);


		Material* debugMaterial = CreateMaterial();
		Shader* debugShader = new Shader();
		debugShader->LoadShader("assets/shaders/glsl/debug/GizmoShader.glslv", "assets/shaders/glsl/Debug/GizmoShader.glslf");
		debugMaterial->SetShader(debugShader);

		Material* debugMaterialInstanced = CreateMaterial();
		Shader* debugShaderInstanced = new Shader();
		debugShaderInstanced->LoadShader("assets/shaders/glsl/debug/GizmoLineShader.glslv", "assets/shaders/glsl/Debug/GizmoLineShader.glslf");
		debugMaterialInstanced->SetShader(debugShaderInstanced);
	}

	MaterialManager::MaterialManager()
	{
		CreateDefaultMaterials();
	}

	MaterialManager::~MaterialManager()
	{

	}

	MaterialManager* MaterialManager::mInstance;

	Material* MaterialManager::CreateMaterial()
	{
		uint32 newMatId = (uint32)mMaterials.size();
		Material* returningMat = new Material(newMatId);
		mMaterials.push_back(returningMat);
		return returningMat;
	}
}