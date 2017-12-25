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
		if (aBindShader && mShader->IsValid())
		{
			mShader->Bind();
			mBound = true;
		}

		if (mTexture && mTexture->IsValid())
		{
			mTexture->Bind();
		}
	}

	void Material::SetDataForDrawing(Shader* aShader)
	{
		Shader* shader = aShader ? aShader : mShader;

		if (shader && shader->IsValid())
		{
			int32 matDiffuseLoc = shader->GetShaderVariableLocation("material.Diffuse");
			int32 matSpecularLoc = shader->GetShaderVariableLocation("material.Specular");
			shader->SetShaderVar(matDiffuseLoc, (void*)&mDiffuseColor, EVarType::Vector4);
			shader->SetShaderVar(matSpecularLoc, (void*)&mSpecular, EVarType::Float);
		}
	}

	void Material::UnBind(bool aUnbindShader)
	{
		if (aUnbindShader && mBound && mShader->IsValid())
		{
			mShader->Unbind();
			mBound = false;
		}
		if (mTexture && mTexture->IsValid())
		{
			mTexture->Unbind();
		}
	}

	uint32 Material::GetShaderVariableLoc(const char* aVariable)
	{
		if(mShader->IsValid())
			return mShader->GetShaderVariableLocation(aVariable);
		
		return 0;
	}

	bool Material::HasAlpha() const
	{
		return mTexture->GetImageFormat() == EImageFormat::RGBA;
	}

	bool Material::IsBound() const
	{
		return mBound;
	}
}