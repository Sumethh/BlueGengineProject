#pragma once
#include "Types.h"
#include "Defines.h"
#include "NonCopyable.h"
namespace BlueGengine
{
	class ShaderImpl;
	class Shader : NonCopyable
	{
	public:

		enum ShaderType
		{
			VertexShader = 0,
			FragmentShader = 1,
			GeometryShader = 2,
			ShaderTypeCount
		};

		Shader();
		~Shader();

		void LoadShader(char* a_vertexShader, char* a_fragmentShader);
		void UnloadShader();

		void Bind();
		void UnBind();

		uint32 GetShaderID();

	private:
		char* m_shaderPaths[ShaderType::ShaderTypeCount];
		ShaderImpl* m_impl;
	};
}