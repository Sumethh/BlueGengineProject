#include "BlueCore/Managers/MaterialManager.h"
#include "BlueCore/Managers/ShaderManager.h"
#include "BlueCore/Graphics/Material.h"
#include "BlueCore/Graphics/Texture2D.h"
#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/Utility/Directory.h"
namespace Blue
{
	void MaterialManager::CreateDefaultMaterials()
	{
		Material* defaultMaterial = CreateMaterial();
		std::string directory = Directory::GetWorkingDirectory();
		ShaderManager::GI()->LoadAndCompileAllShaders("Assets/Shaders");

		Shader* defaultShader = ShaderManager::GI()->GetShader("Forward_Shaded");

		Texture2D* tex = new Texture2D();
		tex->Create();
		tex->LoadTexture("Assets/Textures/Debug.png", EImageFormat::RGB, EPrecisionType::RGB_8Bit);
		defaultMaterial->SetShader(defaultShader);
		defaultMaterial->SetTexture(tex);
		defaultMaterial->SetAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
		defaultMaterial->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		defaultMaterial->SetSpecularPower(0.1f);


		Material* debugMaterial = CreateMaterial();
		Shader* debugShader = ShaderManager::GI()->GetShader("GizmoShader");
		debugMaterial->SetShader(debugShader);

		Material* debugMaterialInstanced = CreateMaterial();
		Shader* debugShaderInstanced = ShaderManager::GI()->GetShader("GizmoLineShader");
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