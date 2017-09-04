#include "BlueCore/Graphics/Material.h"
#include "BlueCore/Graphics/Texture2D.h"
#include "BlueCore/Graphics/Shader.h"
#include <GL/glew.h>

namespace Blue
{
	Material::Material(uint32 aMaterialID) : mId(aMaterialID), mBound(false)
	{
	}

	Material::~Material()
	{

	}

	void Material::Bind(bool aBindShader)
	{
		if (aBindShader)
		{
			mShader->Bind();
			mBound = true;
		}

		if (mTexture)
		{
			mTexture->Bind();
		}
	}

	void Material::SetDataForDrawing(Shader* aShader)
	{
		Shader* shader = aShader ? aShader : mShader;

		if (!aShader)
		{
			int32 matDiffuseLoc = shader->GetShaderVariableLocation("material.Diffuse");
			int32 matSpecularLoc = shader->GetShaderVariableLocation("material.Specular");
			shader->SetShaderVar(matDiffuseLoc, (void*)&mDiffuseColor, EVarType::Vector4);
			shader->SetShaderVar(matSpecularLoc, (void*)&mSpecular, EVarType::Float);
		}
	}

	void Material::UnBind(bool aUnbindShader)
	{
		if (aUnbindShader)
		{
			mShader->UnBind();
			mBound = false;
		}
		if (mTexture)
		{
			mTexture->UnBind();
		}
	}

	uint32 Material::GetShaderVariableLoc(const char* aVariable)
	{
		return mShader->GetShaderVariableLocation(aVariable);
	}

	bool Material::HasAlpha() const
	{
		return mTexture->GetImageFormat() == EImageFormat::RGBA;
	}

	void Material::SetPointLightData(std::vector<Light*>& aLights)
	{
		/*
		    BlueAssert(aLights.size() <= Shader::MaxLightCount);

		    if (mShader->GetPointLightCountLoc() == -1)
		    {
		    return;
		    }

		    float count = (float)aLights.size();
		    mShader->SetShaderVar(mShader->GetPointLightCountLoc(), (void*)&count, EVarType::Float);

		    std::vector<Shader::CachedPointlightShaderInfo>& lightInfo = mShader->GetPointLightInfo();
		    static float constant = 1;
		    static float linear = .14f;
		    static float quadratic = .07f;

		    for (int i = 0; i < aLights.size(); ++i)
		    {
		    Shader::CachedPointlightShaderInfo& info = lightInfo[i];

		    mShader->SetShaderVar(info.pos, (void*)&aLights[i]->position, EVarType::Vector3);
		    mShader->SetShaderVar(info.color, (void*)&aLights[i]->color, EVarType::Vector3);

		    mShader->SetShaderVar(info.constant, (void*)&constant, EVarType::Float);
		    mShader->SetShaderVar(info.linear, (void*)&linear, EVarType::Float);
		    mShader->SetShaderVar(info.quadratic, (void*)&quadratic, EVarType::Float);
		    }*/

	}

	bool Material::IsBound() const
	{
		return mBound;
	}
}