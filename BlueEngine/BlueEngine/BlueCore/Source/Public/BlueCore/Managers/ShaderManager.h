#pragma once
#include "BlueCore/Utility/Directory.h"


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

		void LoadAllShadersInDirectory(const std::string& aPath);
		void LoadShaders(const std::vector<FileInfo>& aFileNames);

		std::map<std::string, Shader*> mShaders;

		std::string mShaderPath;

	};
}