#include "BlueCore/Graphics/Shader.h"
#include "BlueCore/Managers/ShaderManager.h"
#include "BlueCore/Core/Log.h"
#include <fstream>

namespace Blue
{
	static const std::string sVertexShaderExtenstion("sv");
	static const std::string sFragmentShaderExtenstion("sf");
	static const std::string sGeometryShaderExtenstion("sg");

	ShaderManager* ShaderManager::sInstance = nullptr;

	void ShaderManager::LoadAndCompileAllShaders(std::string aPath)
	{
		IGraphicsDevice* graphicsDevice = IGraphicsDevice::GetCurrentGraphicsDevice();
		std::string shaderPath = aPath;
		switch (graphicsDevice->GetGraphicsDeviceType())
		{
			case EGraphicsDeviceType::OpenGL:
				{
					shaderPath += "/GLSL/";
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

		std::map<std::string, Shader*>::iterator foundShader = mShaders.find(aName);

		if (foundShader == mShaders.end())
		{
			return nullptr;
		}
		return foundShader->second;

	}

	void ShaderManager::LoadAllShadersInDirectory(const std::string& aPath)
	{
		std::vector<FileInfo> fileNames;
		std::vector<FileInfo> test;
		std::string testPath("Assets/Models");
		Directory::FindAllFilesInDirectory(testPath, test);

		if (Directory::FindAllFilesInDirectoryAndSubDirectories(aPath, fileNames))
		{
			std::map<std::string, ShaderPair> ShaderPairs;
			LoadShaders(fileNames, ShaderPairs);
			CompileShaders(ShaderPairs);
		}
		else
		{
			Log::Error("Could not find any Shaders to load");
		}
	}

	void ShaderManager::LoadShaders(const std::vector<FileInfo>& aFileNames, std::map<std::string, ShaderPair>& aOutShaderPairs)
	{
		for (sizeInt i = 0; i < aFileNames.size(); ++i)
		{
			const FileInfo& currentFileInfo = aFileNames[i];
			ShaderPair& currentShaderPair = aOutShaderPairs[currentFileInfo.fileName];

			if (currentFileInfo.extension == sVertexShaderExtenstion)
			{
				currentShaderPair.shaderCount++;
				currentShaderPair.shaders[Shader::EShaderType::VertexShader] = currentFileInfo.path;
			}
			else if (currentFileInfo.extension == sFragmentShaderExtenstion)
			{
				currentShaderPair.shaderCount++;
				currentShaderPair.shaders[Shader::EShaderType::FragmentShader] = currentFileInfo.path;
			}
			else if (currentFileInfo.extension == sGeometryShaderExtenstion)
			{
				currentShaderPair.shaderCount++;
				currentShaderPair.shaders[Shader::EShaderType::GeometryShader] = currentFileInfo.path;
			}
			else
			{
				std::string message("Ignoring the loading of shader: ");
				message += currentFileInfo.fileName + currentFileInfo.path;
				Log::Warning(message);
			}
		}
	}

	void ShaderManager::CompileShaders(const std::map<std::string, ShaderPair>& aShaders)
	{
		Shader* shader = nullptr;
		for (auto& currentShader : aShaders)
		{
			const ShaderPair& shaderPair = currentShader.second;
			const std::string& shaderName = currentShader.first;
			BlueAssert(shaderName.size() && shaderPair.shaderCount);
			BlueAssert(mShaders.find(currentShader.first) == mShaders.end());

			shader = new Shader();

			if (shaderPair.shaderCount == 2)
			{
				shader->LoadShader(shaderPair.shaders[Shader::EShaderType::VertexShader], shaderPair.shaders[Shader::EShaderType::FragmentShader]);
			}
			else
			{
				BlueAssert(false);
			}
			mShaders[shaderName] = shader;
		}
	}

}