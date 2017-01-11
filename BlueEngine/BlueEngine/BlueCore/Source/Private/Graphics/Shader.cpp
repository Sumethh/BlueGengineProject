#include "Graphics/Shader.h"
#include <string>
namespace BlueCore
{
	const	uint32 Shader::MaxLightCount;
	Shader::Shader() : mPointLightCountLoc(-1)
	{
		mShaderResourceID = IGraphicsDevice::GetCurrentGraphicsDevice()->CreateGraphicsResource(EGraphicsResourceType::Shader);
	}

	Shader::~Shader()
	{
		UnloadShader();
	}

	void Shader::LoadShader(char* aVertexShader, char* aFragmentShader)
	{
		IGraphicsDevice* gr = IGraphicsDevice::GetCurrentGraphicsDevice();
		gr->UpdateResourceData(mShaderResourceID, aVertexShader, aFragmentShader);
		m_shaderPaths[ShaderType::VertexShader] = aVertexShader;
		m_shaderPaths[ShaderType::FragmentShader] = aFragmentShader;
		Bind();
		CalcPointLightInfo();
		UnBind();
	}

	void Shader::UnloadShader()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->DeleteGraphicsResource(mShaderResourceID);
	}

	void Shader::Bind()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->BindGraphicsResource(mShaderResourceID);
	}

	void Shader::UnBind()
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->UnBindGraphicsResource(mShaderResourceID);
	}

	int32 Shader::GetShaderVariableLocation(const char* aVarName)
	{
		return IGraphicsDevice::GetCurrentGraphicsDevice()->GetShaderVariableLocation(mShaderResourceID, aVarName);
	}

	void Shader::SetShaderVar(uint32 aVarLoc, void* aVar, EVarType aType)
	{
		IGraphicsDevice::GetCurrentGraphicsDevice()->SetShaderVariable(aVarLoc, aVar, aType);
	}

	void Shader::CalcPointLightInfo()
	{
		int32 val = GetShaderVariableLocation("pointLightCount");

		if (val != -1)
		{
			mPointLightCountLoc = val;

			for (int i = 0; i < MaxLightCount; ++i)
			{
				std::string base = "pointLights";
				base += '[' + std::to_string(i) + "].";
				CachedPointlightShaderInfo info;
				std::string varName;
				varName = base;
				varName += "position";
				info.pos = GetShaderVariableLocation(varName.c_str());
				varName = base;
				varName += "color";
				info.color = GetShaderVariableLocation(varName.c_str());
				varName = base;
				varName += "constant";
				info.constant = GetShaderVariableLocation(varName.c_str());
				varName = base;
				varName += "linear";
				info.linear = GetShaderVariableLocation(varName.c_str());
				varName = base;
				varName += "quadratic";
				info.quadratic = GetShaderVariableLocation(varName.c_str());
				mCachedPointLightInfo.push_back(info);
			}
		}
	}

}