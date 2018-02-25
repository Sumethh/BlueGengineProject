#include "BlueCore/Graphics/Shader.h"
#include <string>

namespace Blue
{
	const	uint32 Shader::MaxLightCount;
	Shader::Shader() : mPointLightCountLoc(-1)
	{
	}

	Shader::~Shader()
	{
	}

	void Shader::Create()
	{
		IGraphicsDevice* device = IGraphicsDevice::GetCurrentGraphicsDevice();
		mGraphicsResource = device->CreateGraphicsResource(EGraphicsResourceType::Shader);
	}

	void Shader::UpdateResource()
	{
		BlueAssert(IsValid());
		LoadShader(m_shaderPaths[static_cast<int32>(EShaderType::VertexShader)], m_shaderPaths[static_cast<int32>(EShaderType::FragmentShader)]);
	}

	void Shader::LoadShader(const std::string& aVertexShader, const std::string& aFragmentShader)
	{
		IGraphicsDevice* gr = IGraphicsDevice::GetCurrentGraphicsDevice();
		gr->UpdateResourceData(mGraphicsResource, aVertexShader, aFragmentShader);
		m_shaderPaths[EShaderType::VertexShader] = aVertexShader;
		m_shaderPaths[EShaderType::FragmentShader] = aFragmentShader;
		Bind();
		CalcPointLightInfo();
		Unbind();
	}

	void Shader::SetShaderPaths(const std::string& aVertexShader, const std::string& aFragmentShader)
	{
		m_shaderPaths[EShaderType::VertexShader] = aVertexShader;
		m_shaderPaths[EShaderType::FragmentShader] = aFragmentShader;
	}

	int32 Shader::GetShaderVariableLocation(const char* aVarName)
	{
		return IGraphicsDevice::GetCurrentGraphicsDevice()->GetShaderVariableLocation(mGraphicsResource, aVarName);
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
				mCachedPointLightInfo.emplace_back(std::move(info));
			}
		}
	}
}