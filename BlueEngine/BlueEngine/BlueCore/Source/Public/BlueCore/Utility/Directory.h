#pragma once

#include "File.h"

#include <string>
#include <vector>
namespace Blue
{
	class Directory
	{
	public:

		static bool FindAllFilesInDirectory(const std::string& aDirectory, std::vector<FileInfo>& aOutFileInfo);
		static bool FindAllFilesInDirectoryAndSubDirectories(const std::string& aDirectory, std::vector<FileInfo>& aOutFileInfo);
		static bool FindAllFoldersInDirectory(const std::string& aDirectory, std::vector<FileInfo>& aOutFileInfo);
		static bool DoesDirectoryExist(const std::string& aDirectory);
		static std::string GetWorkingDirectory();
	private:

	};
}