#pragma once
#include "../Types.h"

namespace BlueGengine
{
	class ShaderImpl
	{
	public:
		ShaderImpl() {};
		virtual ~ShaderImpl() {};

		virtual void LoadShader(char* a_vertexShaderPath, char* a_fragmentShaderPath) = 0;
		virtual void UnloadShader() = 0;
		virtual void ReloadShader() = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual uint32 GetShaderID() = 0;
	};

	class OpenGlShaderImpl : public ShaderImpl
	{
		virtual void LoadShader(char* a_vertexShaderPath, char* a_fragmentShaderPath);
		virtual void UnloadShader() ;
		virtual void ReloadShader();
		virtual void Bind() ;
		virtual void UnBind();
		virtual uint32 GetShaderID() {return m_programID;}
	private:
		uint32 LoadAndCompileShader(int32 a_shaderType, char* a_path);
		uint32 m_programID;

	};

}