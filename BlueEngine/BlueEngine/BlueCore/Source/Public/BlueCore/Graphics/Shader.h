#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/GraphicsDevice/IGraphicsDevice.h"
#include "BlueCore/Graphics/GraphicsResource.h"
#include <vector>
#include <glm/glm.hpp>

namespace Blue
{
	class Shader : public NonCopyable, public GraphicsResource
	{
	public:

		struct CachedPointlightShaderInfo
		{
			int32 pos;
			int32 color;
		};

		enum EShaderType
		{
			VertexShader = 0,
			FragmentShader = 1,
			GeometryShader = 2,
			ShaderTypeCount
		};

		Shader();
		~Shader();

		virtual void Create() override;
		virtual void UpdateResource() override;

		void LoadShader(const std::string& aVertexShader, const std::string& aFragmentShader);
		void SetShaderPaths(const std::string& aVertexShader, const std::string& aFragmentShader);
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

		std::string m_shaderPaths[EShaderType::ShaderTypeCount];
		int32 mPointLightCountLoc;
		std::vector<CachedPointlightShaderInfo> mCachedPointLightInfo;
	};
}