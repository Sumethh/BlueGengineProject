#pragma once
#include <string>
#include <map>

namespace Blue
{
	class Shader;
	class ShaderManager
	{
	public:

		void LoadAndCompileAllShaders(std::string aPath);
		void RecompileChangedShaders();

		Shader* GetShader(std::string aName);

		static ShaderManager* GI()
		{
			if (!sInstance)
				sInstance = new ShaderManager();
			return sInstance;
		}

	private:
		static ShaderManager* sInstance;
		std::string mShaderPath;
	};
}