#pragma once
#include "../Types.h"

namespace BlueGengine
{
	enum ShaderVarType
	{
		SVT_float,
		SVT_vec3,
		SVT_mat4
	};
	class ShaderImpl
	{
		public:
		ShaderImpl() {};
		virtual ~ShaderImpl() {};

		virtual void LoadShader(char* aVertexShaderPath, char* aFragmentShaderPath) = 0;
		virtual void UnloadShader() = 0;
		virtual void ReloadShader() = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual uint32 GetShaderID() = 0;
		virtual int32 GetShaderVariableLocation(const char* aVarName) = 0;
		virtual void SetShaderVariable(uint32 aVarLoc, void* aData, ShaderVarType varType) = 0;
	};

	class OpenGlShaderImpl : public ShaderImpl
	{
		virtual void LoadShader(char* aVertexShaderPath, char* aFragmentShaderPath);
		virtual void UnloadShader() ;
		virtual void ReloadShader();
		virtual void Bind() ;
		virtual void UnBind();
		virtual uint32 GetShaderID() {return mProgramID;}
		virtual int32 GetShaderVariableLocation(const char* aVarName);
		virtual void SetShaderVariable(uint32 aVarLoc, void* aData, ShaderVarType varType);

		private:
		uint32 LoadAndCompileShader(int32 aShaderType, char* aPath);
		uint32 mProgramID;

	};

}