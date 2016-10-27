#include "MaterialManager.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"
namespace BlueGengine
{

	MaterialManager::MaterialManager()
	{
		Material* defaultMaterial = CreateMaterial();
		Shader* shader = new Shader();
		shader->LoadShader("assets/shaders/glsl/SimpleShader.glslv", "assets/shaders/glsl/SimpleShader.glslf");
		Texture* tex = new Texture();
		tex->LoadTexture("Assets/Textures/Default.png", ImageFormat::IF_RGB, ImageFormat::IF_RGB);
		defaultMaterial->SetShader(shader);
		defaultMaterial->SetTexture(tex);
		defaultMaterial->SetAmbientColor(glm::vec4(0.1f, 0.1f, 0.1f, 0.1f));
		defaultMaterial->SetDiffuseColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		defaultMaterial->SetSpecularPower(0.1f);
	}

	MaterialManager::~MaterialManager()
	{

	}

	MaterialManager* MaterialManager::m_instance;

	Material* MaterialManager::CreateMaterial()
	{
		uint32 newMatId = (uint32)m_materials.size();
		Material* returningMat = new Material(newMatId);
		m_materials.push_back(returningMat);
		return returningMat;
	}

}