#include "ShaderImpl.h"
#include "../Defines.h"

#include <GL/glew.h>
#include <fstream>
#include <sstream>
#include <iostream>
namespace BlueGengine
{

	void OpenGlShaderImpl::LoadShader(char* aVertexShaderPath, char* aFragmentShaderPath)
	{
		uint32 vertexShader = LoadAndCompileShader(GL_VERTEX_SHADER, aVertexShaderPath);

		uint32 fragmentShader = LoadAndCompileShader(GL_FRAGMENT_SHADER, aFragmentShaderPath);

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

		if (mProgramID)
		{
			glDeleteProgram(mProgramID);
		}

		mProgramID = programID;
	}

	void OpenGlShaderImpl::UnloadShader()
	{
		if (mProgramID)
		{
			glDeleteProgram(mProgramID);
			mProgramID = 0;
		}
	}

	void OpenGlShaderImpl::ReloadShader()
	{
		BlueAssert(false);
	}

	void OpenGlShaderImpl::Bind()
	{
		glUseProgram(mProgramID);

	}

	void OpenGlShaderImpl::UnBind()
	{
		glUseProgram(0);

	}

	int32 OpenGlShaderImpl::GetShaderVariableLocation(const char* aVarName)
	{
		return glGetUniformLocation(mProgramID, aVarName);
	}

	void OpenGlShaderImpl::SetShaderVariable(uint32 aVarLoc, void* aData, ShaderVarType varType)
	{
		float* data;

		switch (varType)
		{
			case BlueGengine::SVT_float:
				glUniform1f(aVarLoc, (*(float*)aData));
				break;

			case BlueGengine::SVT_vec3:
				data = (float*)aData;
				glUniform3f(aVarLoc, *data, *(data + 1), *(data + 2));
				break;

			case BlueGengine::SVT_mat4:
				glUniformMatrix4fv(aVarLoc, 1, GL_FALSE, (float*)aData);
				break;

			default:
				break;
		}
	}

	uint32 OpenGlShaderImpl::LoadAndCompileShader(int32 aShaderType, char* aPath)
	{
		std::string shaderSource;
		std::stringstream stringStream;
		std::ifstream file;
		file.open(aPath);

		if (!file.is_open())
		{
			std::cout << "File failed to open: " << aPath << std::endl;
			return 0;
		}

		stringStream << file.rdbuf();
		shaderSource = stringStream.str();

		uint32 shaderID = glCreateShader(aShaderType);
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