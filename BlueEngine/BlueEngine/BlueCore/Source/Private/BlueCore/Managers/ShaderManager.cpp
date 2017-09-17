#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/Managers/ShaderManager.h"
#include "BlueCore/Utility/Directory.h"


namespace Blue
{
	ShaderManager* ShaderManager::sInstance = nullptr;

	void ShaderManager::LoadAndCompileAllShaders(std::string aPath)
	{
		mShaderPath = aPath;
		std::vector<std::string> fileNames;
		Directory::FindAllFilesInDirectory(aPath, fileNames);
		int t = 0;
	}

	void ShaderManager::RecompileChangedShaders()
	{

	}

	Shader* ShaderManager::GetShader(std::string aName)
	{
		return nullptr;
	}

}