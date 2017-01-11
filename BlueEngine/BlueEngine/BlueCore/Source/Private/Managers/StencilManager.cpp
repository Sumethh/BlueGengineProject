#include "Managers/StencilManager.h"
#include "Serialization/ArchiveObject.h"
#include "Core/Log.h"
#include <windows.h>
#include <vector>
namespace BlueCore
{

	std::vector<std::string> FindFileNamesInDir(char* dir)
	{
		std::vector<std::string> foundFileNames;
		HANDLE hFind;
		WIN32_FIND_DATA data = {};
		hFind = FindFirstFile(dir, &data);

		while (hFind != INVALID_HANDLE_VALUE)
		{
			foundFileNames.push_back(data.cFileName);

			if (!FindNextFile(hFind, &data))
			{
				break;
			}
		}

		return foundFileNames;
	}




	void StencilManager::Init()
	{
		mStencils.clear();
		std::vector <std::string> fileNames = FindFileNamesInDir("Assets/Stencils/*");

		for (auto t  = fileNames.begin(); t != fileNames.end();)
		{
			if ((*t).find(".stencil") == std::string::npos)
			{
				t = fileNames.erase(t);
			}
			else
			{
				t++;
			}
		}

		CreateStencils(fileNames);

	}

	BlueCore::Stencil* StencilManager::GetStencil(std::string stencilName)
	{
		auto it = mStencils.find(stencilName);

		if (it == mStencils.end())
		{
			return nullptr;
		}

		return (*it).second;
	}

	void StencilManager::CreateStencils(std::vector<std::string>& fileNames)
	{
		std::string path = "Assets/Stencils/";

		for (auto fileName : fileNames)
		{
			std::string file = path + fileName;
			ArchiveObject archive("lol");
			archive.ReadFromFile(file.c_str());
			Stencil* stencil = new Stencil("");
			stencil->OnDeserialize(&archive);
			mStencils[stencil->Name()] = stencil;
			static std::string loadedMessage = "Loaded Stencil: ";
			Log::LogInfo(loadedMessage + stencil->Name());
		}
	}

}