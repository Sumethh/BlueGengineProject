#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/Managers/ShaderManager.h"
#include <fstream>

namespace Blue
{

	static const char sVertexShaderExtention[] = ".glsv";
	static const char sFragmentShaderExtention[] = ".glsf";


	ShaderManager* ShaderManager::sInstance = nullptr;

	void ShaderManager::LoadAndCompileAllShaders(std::string aPath)
	{

		IGraphicsDevice* graphicsDevice = IGraphicsDevice::GetCurrentGraphicsDevice();
		std::string shaderPath = aPath;
		switch (graphicsDevice->GetGraphicsDeviceType())
		{
			case EGraphicsDeviceType::OpenGL:
				{
					aPath += "/GLSL/";
					break;
				}
			case EGraphicsDeviceType::D3D11:
				{
					break;
				}
				InvalidDefaultCase;
		}
		mShaderPath = shaderPath;
		LoadAllShadersInDirectory(shaderPath);
	}

	void ShaderManager::RecompileChangedShaders()
	{

	}

	Shader* ShaderManager::GetShader(std::string aName)
	{
		return nullptr;
	}

	void ShaderManager::LoadAllShadersInDirectory(const std::string& aPath)
	{
		std::vector<FileInfo> fileNames;
		Directory::FindAllFilesInDirectory(aPath, fileNames);
		if (fileNames.size())
		{

		}
	}

	void ShaderManager::LoadShaders(const std::vector<FileInfo>& aFileNames)
	{
		struct ShaderPair
		{
			std::string shaders[Shader::EShaderType::ShaderTypeCount];
		};
		std::vector<ShaderPair> shaderPairs;

		for (sizeInt i = 0; i < aFileNames.size(); ++i)
		{
			ShaderPair currentPair;

			const FileInfo& fileInfo = aFileNames[i];
			for (sizeInt h = i + 1; h < aFileNames.size(); ++i)
			{
			}
			shaderPairs.emplace_back(std::move(currentPair));

		}

	}

}