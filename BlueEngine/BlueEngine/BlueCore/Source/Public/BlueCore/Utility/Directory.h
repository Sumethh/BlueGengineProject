#pragma once

#include "File.h"

#include <string>
#include <vector>
namespace Blue
{
	class Directory
	{
	public:

		static bool FindAllFilesInDirectory(std::string aDirectory, std::vector<FileInfo>& aOutFileInfo);
		static bool FindAllFoldersInDirecory(std::string aDirectory, std::vector<FileInfo>& aOutFileInfo);
		static bool DoesDirectoryExist(std::string aDirectory);
		static std::string GetWorkingDirectory();
	private:

	};
}