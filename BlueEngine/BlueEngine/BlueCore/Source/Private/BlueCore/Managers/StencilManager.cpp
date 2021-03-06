#include "BlueCore/Managers/StencilManager.h"
#include "BlueCore/Serialization/ArchiveObject.h"
#include "BlueCore/Core/Log.h"
//#include <windows.h>
#include <vector>

namespace Blue
{
	
	void StencilManager::Init()
	{
		mStencils.clear();
		std::vector <std::string> fileNames;

		for (auto t = fileNames.begin(); t != fileNames.end();)
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

	Stencil* StencilManager::GetStencil(std::string stencilName)
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
			Log::Info(loadedMessage + stencil->Name());
		}
	}
}