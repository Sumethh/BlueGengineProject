#include "MaterialManager.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
namespace BlueGengine
{

	void MaterialManager::CreateDefaultMaterials()
	{
		Material* defaultMaterial = CreateMaterial();
		Shader* shader = new Shader();
		shader->LoadShader("assets/shaders/glsl/Forward/Forward_Shaded.glslv", "assets/shaders/glsl/Forward/Forward_Shaded.glslf");
		Texture* tex = new Texture();
		tex->LoadTexture("Assets/Textures/Default.png", ImageFormat::IF_RGB, ImageFormat::IF_RGB);
		defaultMaterial->SetShader(shader);
		defaultMaterial->SetTexture(tex);
		defaultMaterial->SetAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
		defaultMaterial->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		defaultMaterial->SetSpecularPower(0.1f);


		Material* debugMaterial = CreateMaterial();
		Shader* debugShader = new Shader();
		debugShader->LoadShader("assets/shaders/glsl/debug/GizmoShader.glslv", "assets/shaders/glsl/Debug/GizmoShader.glslf");
		debugMaterial->SetShader(debugShader);
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