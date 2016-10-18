#include "Shader.h"
#include "impl/ShaderImpl.h"
namespace BlueGengine
{
	Shader::Shader()
	{
		m_impl = new OpenGlShaderImpl();
	}

	Shader::~Shader()
	{
		if (m_impl)
		{
			m_impl->UnloadShader();
			delete m_impl;
		}
	}

	void Shader::LoadShader(char* a_vertexShader, char* a_fragmentShader)
	{
		m_impl->LoadShader(a_vertexShader, a_fragmentShader);
		m_shaderPaths[ShaderType::VertexShader] = a_vertexShader;
		m_shaderPaths[ShaderType::FragmentShader] = a_fragmentShader;

	}

	void Shader::UnloadShader()
	{
		m_impl->UnloadShader();
	}

	void Shader::Bind()
	{
		m_impl->Bind();
	}

	void Shader::UnBind()
	{
		m_impl->UnBind();
	}

	uint32 Shader::GetShaderID()
	{
		return m_impl->GetShaderID();
	}

}