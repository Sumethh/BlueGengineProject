#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include <GL/glew.h>
namespace BlueGengine
{
	Material::Material(uint32 a_materialID) : m_id(a_materialID)
	{
	}

	Material::~Material()
	{

	}

	void Material::PrepareForDrawing()
	{
		m_shader->Bind();
		m_texture->Bind();
		uint32 shaderID = m_shader->GetShaderID();

		int32 matDiffuseLoc = glGetUniformLocation(shaderID, "material.Diffuse");
		int32 matAmbientLoc = glGetUniformLocation(shaderID, "material.Ambient");
		int32 matSpecularLoc = glGetUniformLocation(shaderID, "material.Specular");


		glUniform4f(matDiffuseLoc, m_diffuseColor.x, m_diffuseColor.y, m_diffuseColor.z, m_diffuseColor.w);
		glUniform4f(matAmbientLoc, m_ambientColor.x, m_ambientColor.y, m_ambientColor.z, m_ambientColor.w);
		glUniform1f(matSpecularLoc, m_specular);
	}

	void Material::Unprep()
	{
		m_shader->UnBind();
		m_texture->UnBind();
	}

}