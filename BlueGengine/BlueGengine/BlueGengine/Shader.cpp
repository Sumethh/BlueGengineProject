#include "Shader.h"
#include "impl/ShaderImpl.h"
#include <string>
namespace BlueGengine
{
	const	uint32 Shader::MaxLightCount;
	Shader::Shader() : mPointLightCountLoc(-1)
	{
		mImpl = new OpenGlShaderImpl();
	}

	Shader::~Shader()
	{
		if (mImpl)
		{
			mImpl->UnloadShader();
			delete mImpl;
		}
	}

	void Shader::LoadShader(char* aVertexShader, char* aFragmentShader)
	{
		mImpl->LoadShader(aVertexShader, aFragmentShader);
		m_shaderPaths[ShaderType::VertexShader] = aVertexShader;
		m_shaderPaths[ShaderType::FragmentShader] = aFragmentShader;
		Bind();
		CalcPointLightInfo();
		UnBind();
	}

	void Shader::UnloadShader()
	{
		mImpl->UnloadShader();
	}

	void Shader::Bind()
	{
		mImpl->Bind();
	}

	void Shader::UnBind()
	{
		mImpl->UnBind();
	}

	int32 Shader::GetShaderVariableLocation(const char* aVarName)
	{
		return mImpl->GetShaderVariableLocation(aVarName);
	}

	uint32 Shader::GetShaderID()
	{
		return mImpl->GetShaderID();
	}

	void Shader::SetMatrixShaderVar(uint32 aVarLoc, glm::mat4* aVar)
	{
		mImpl->SetShaderVariable(aVarLoc, (void*)aVar, SVT_mat4);
	}

	void Shader::SetVectorShaderVar(uint32 aVarLoc, glm::vec3* aVar)
	{
		mImpl->SetShaderVariable(aVarLoc, (void*)aVar, SVT_vec3);

	}

	void Shader::SetFloatShaderVar(uint32 aVarLoc, float* aVar)
	{
		mImpl->SetShaderVariable(aVarLoc, (void*)aVar, SVT_float);

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