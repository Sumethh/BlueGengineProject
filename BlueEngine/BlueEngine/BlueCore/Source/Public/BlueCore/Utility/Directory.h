#pragma once
#include <string>
#include <vector>
namespace Blue
{
	class Directory
	{
	public:

		static bool FindAllFilesInDirectory(std::string aDirectory, std::vector<std::string>& aOutFileNames);
		static bool FindAllFoldersInDirecory(std::string aDirectory, std::vector<std::string>& aOutFileNames);
		static std::string GetWorkingDirectory();
	private:

	};
}