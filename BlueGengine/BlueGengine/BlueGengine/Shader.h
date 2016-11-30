#pragma once
#include "Types.h"
#include "Defines.h"
#include "NonCopyable.h"
#include <vector>
#include <glm/glm.hpp>
#include "Graphics/IGraphicsDevice.h"
namespace BlueGengine
{
	class ShaderImpl;
	class Shader : NonCopyable
	{
		public:

		struct CachedPointlightShaderInfo
		{
			int32 pos;
			int32 color;
			int32 constant;
			int32 linear;
			int32 quadratic;
		};

		enum ShaderType
		{
			VertexShader = 0,
			FragmentShader = 1,
			GeometryShader = 2,
			ShaderTypeCount
		};

		Shader();
		~Shader();

		void LoadShader(char* aVertexShader, char* aFragmentShader);
		void UnloadShader();

		void Bind();
		void UnBind();
		int32 GetShaderVariableLocation(const char* aVarName);

		void SetShaderVar(uint32 aVarLoc, void* aVar, EVarType aType);

		inline std::vector<CachedPointlightShaderInfo>& GetPointLightInfo() { return mCachedPointLightInfo; }
		inline int32 GetPointLightCountLoc() { return mPointLightCountLoc; }
		static const uint32 MaxLightCount = 32;

		private:
		void CalcPointLightInfo();

		char* m_shaderPaths[ShaderType::ShaderTypeCount];
		int32 mPointLightCountLoc;
		std::vector<CachedPointlightShaderInfo> mCachedPointLightInfo;
		uint32 mShaderResourceID;
	};
}