#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include <vector>
#include <glm/glm.hpp>

namespace Blue
{
	class Shader : NonCopyable
	{
	public:

		struct CachedPointlightShaderInfo
		{
			int32 pos;
			int32 color;
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

		inline std::vector<CachedPointlightShaderInfo>& GetPointLightInfo()
		{
			return mCachedPointLightInfo;
		}
		inline int32 GetPointLightCountLoc()
		{
			return mPointLightCountLoc;
		}
		static const uint32 MaxLightCount = 64;

	private:
		void CalcPointLightInfo();

		char* m_shaderPaths[ShaderType::ShaderTypeCount];
		int32 mPointLightCountLoc;
		std::vector<CachedPointlightShaderInfo> mCachedPointLightInfo;
		GraphicsDeviceResourceID mShaderResourceID;
	};
}