#include "Graphics/Material.h"
#include "Graphics/Texture2D.h"
#include "Graphics/Shader.h"
#include <GL/glew.h>
Material::Material(uint32 aMaterialID) : mId(aMaterialID)
{
}

Material::~Material()
{

}

void Material::Bind()
{
	mShader->Bind();

	if (mTexture)
	{
		mTexture->Bind();
	}
}

void Material::SetDataForDrawing()
{
	int32 matDiffuseLoc =  mShader->GetShaderVariableLocation("material.Diffuse");
	int32 matSpecularLoc = mShader->GetShaderVariableLocation("material.Specular");


	mShader->SetShaderVar(matDiffuseLoc, (void*)&mDiffuseColor, EVarType::Vector4);
	mShader->SetShaderVar(matSpecularLoc, (void*)&mSpecular, EVarType::Float);
}

void Material::UnBind()
{
	mShader->UnBind();

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
	return mTexture->GetImageFormat() == ImageFormat::RGBA;
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