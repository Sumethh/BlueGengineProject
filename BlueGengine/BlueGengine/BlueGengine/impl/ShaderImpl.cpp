#include "ShaderImpl.h"
#include "../Defines.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
namespace BlueGengine
{

	void OpenGlShaderImpl::LoadShader(char* a_vertexShaderPath, char* a_fragmentShaderPath)
	{
		uint32 vertexShader = LoadAndCompileShader(GL_VERTEX_SHADER, a_vertexShaderPath);

		uint32 fragmentShader = LoadAndCompileShader(GL_FRAGMENT_SHADER, a_fragmentShaderPath);

		if (!vertexShader || !fragmentShader)
		{
			std::cout << "A shader failed to load" << std::endl;
			return;
		}

		uint32 programID = glCreateProgram();

		glAttachShader(programID, vertexShader);

		glAttachShader(programID, fragmentShader);

		glLinkProgram(programID);

		int32 success;
		glGetProgramiv(programID, GL_LINK_STATUS, &success);

		if (!success)
		{
			char infoLog[1028];
			glGetProgramInfoLog(programID, 1028, NULL, infoLog);
			std::cout << "PROGRAM FAILED TO LINK" << std::endl << infoLog << std::endl;
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
			return;
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		if (m_programID)
		{
			glDeleteProgram(m_programID);
		}

		m_programID = programID;
	}

	void OpenGlShaderImpl::UnloadShader()
	{
		if (m_programID)
		{
			glDeleteProgram(m_programID);
			m_programID = 0;
		}
	}

	void OpenGlShaderImpl::ReloadShader()
	{
		BlueAssert(false);
	}

	void OpenGlShaderImpl::Bind()
	{
		glUseProgram(m_programID);

	}

	void OpenGlShaderImpl::UnBind()
	{
		glUseProgram(0);

	}

	uint32 OpenGlShaderImpl::LoadAndCompileShader(int32 a_shaderType, char* a_path)
	{
		std::string shaderSource;
		std::stringstream stringStream;
		std::ifstream file;
		file.open(a_path);

		if (!file.is_open())
		{
			std::cout << "File failed to open: " << a_path << std::endl;
			return 0;
		}

		stringStream << file.rdbuf();
		shaderSource = stringStream.str();

		uint32 shaderID = glCreateShader(a_shaderType);
		const char* source = shaderSource.c_str();
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);
		int32 success;
		char infoLog[1028];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shaderID, 1028, NULL, infoLog);
			std::cout << "SHADER COMPILE FAILED" << std::endl << infoLog << std::endl;
			return 0;
		}

		return shaderID;
	}

}