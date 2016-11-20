#include "Material.h"
#include "Texture.h"
#include "Shader.h"
#include <GL/glew.h>
namespace BlueGengine
{
	Material::Material(uint32 aMaterialID) : mId(aMaterialID)
	{
	}

	Material::~Material()
	{

	}

	void Material::Bind()
	{
		m_shader->Bind();

		if (mTexture)
		{
			mTexture->Bind();
		}
	}

	void Material::SetDataForDrawing()
	{
		uint32 shaderID = m_shader->GetShaderID();
		int32 matDiffuseLoc = glGetUniformLocation(shaderID, "material.Diffuse");
		int32 matSpecularLoc = glGetUniformLocation(shaderID, "material.Specular");


		glUniform4f(matDiffuseLoc, mDiffuseColor.x, mDiffuseColor.y, mDiffuseColor.z, mDiffuseColor.w);
		glUniform1f(matSpecularLoc, mSpecular);
	}

	void Material::Unprep()
	{
		m_shader->UnBind();
		mTexture->UnBind();
	}

	uint32 Material::GetShaderVariableLoc(const char* aVariable)
	{
		return glGetUniformLocation(m_shader->GetShaderID(), aVariable);
	}

	void Material::SetPointLightData(std::vector<Light*>& aLights)
	{
		BlueAssert(aLights.size() <= Shader::MaxLightCount);

		if (m_shader->GetPointLightCountLoc() == -1)
		{
			return;
		}

		float count = (float)aLights.size();
		m_shader->SetFloatShaderVar(m_shader->GetPointLightCountLoc(), &count);

		std::vector<Shader::CachedPointlightShaderInfo>& lightInfo = m_shader->GetPointLightInfo();
		static float constant = 1;
		static float linear = .14;
		static float quadratic = .07f;

		for (int i = 0; i < aLights.size(); ++i)
		{
			Shader::CachedPointlightShaderInfo& info = lightInfo[i];

			m_shader->SetVectorShaderVar(info.pos, &aLights[i]->position);
			m_shader->SetVectorShaderVar(info.color, & aLights[i]->color);

			m_shader->SetFloatShaderVar(info.constant, &constant);
			m_shader->SetFloatShaderVar(info.linear, &linear);
			m_shader->SetFloatShaderVar(info.quadratic, &quadratic);

		}

	}
}