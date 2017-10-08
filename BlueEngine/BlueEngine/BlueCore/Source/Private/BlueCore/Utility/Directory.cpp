#include "Bluecore/Utility/Directory.h"
#include "BlueCore/Core/Log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <algorithm>
namespace Blue
{

	enum class EFileFlags : uint8
	{
		Directory = BlueBit(0),
		File = BlueBit(1)
	};

	uint8 ConvertToEFileFlags(DWORD aFlags)
	{
		uint8 outFlags = 0;
		if (aFlags & FILE_ATTRIBUTE_DIRECTORY)
			outFlags |= static_cast<uint8>(EFileFlags::Directory);
		else if (aFlags & FILE_ATTRIBUTE_ARCHIVE)
			outFlags |= static_cast<uint8>(EFileFlags::File);

		return outFlags;
	}

	bool FindFilesInDirectory(std::string aDirectory, std::vector<FileInfo>& aOutFileNames, EFileFlags aFlags)
	{
		WIN32_FIND_DATA findData;
		LARGE_INTEGER fileSize;
		HANDLE foundResult = INVALID_HANDLE_VALUE;
		DWORD error = 0;
		std::string searchingDir(aDirectory + "\\*");
		std::replace(searchingDir.begin(), searchingDir.end(), '/', '\\');
		if (searchingDir.size() > MAX_PATH - 3)
		{
			Log::Error("Directory is too long: " + searchingDir);
			return false;
		}

		foundResult = FindFirstFile(searchingDir.c_str(), &findData);

		if (foundResult == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			Log::Error("Could not find a file in the supplied directory: " + aDirectory);
			return false;
		}
		uint8 fileFlags = ConvertToEFileFlags(findData.dwFileAttributes);

		FileInfo currentFileInfo{};

		if (fileFlags & static_cast<uint8>(aFlags))
		{
			std::string fullFileName(findData.cFileName);
			sizeInt extensionLocation = fullFileName.find_first_of('.');
			currentFileInfo.path = aDirectory + fullFileName;
			currentFileInfo.fileName = fullFileName.substr(0, extensionLocation);
			currentFileInfo.extension = fullFileName.substr(extensionLocation + 1, fullFileName.size() - extensionLocation - 1);
			aOutFileNames.emplace_back(currentFileInfo);
		}

		DWORD t = FILE_ATTRIBUTE_DIRECTORY;
		DWORD A = FILE_ATTRIBUTE_ARCHIVE;
		while (FindNextFile(foundResult, &findData))
		{
			fileFlags = ConvertToEFileFlags(findData.dwFileAttributes);
			if (fileFlags & static_cast<uint8>(aFlags))
			{
				currentFileInfo = {};
				std::string fullFileName(findData.cFileName);
				sizeInt extensionLocation = fullFileName.find_first_of('.');
				currentFileInfo.path = aDirectory + fullFileName;
				currentFileInfo.fileName = fullFileName.substr(0, extensionLocation);
				currentFileInfo.extension = fullFileName.substr(extensionLocation + 1, fullFileName.size() - extensionLocation - 1);
				aOutFileNames.emplace_back(currentFileInfo);
			}
		}
		FindClose(foundResult);
		return aOutFileNames.size() > 0;
	}

	bool Directory::FindAllFilesInDirectory(std::string aDirectory, std::vector<FileInfo>& aOutFileNames)
	{
		return FindFilesInDirectory(aDirectory, aOutFileNames, EFileFlags::File);
	}

	bool Directory::FindAllFoldersInDirecory(std::string aDirectory, std::vector<FileInfo>& aOutFileNames)
	{
		return FindFilesInDirectory(aDirectory, aOutFileNames, EFileFlags::Directory);
	}

	bool Directory::DoesDirectoryExist(std::string aDirectory)
	{
		return false;
	}

	std::string Directory::GetWorkingDirectory()
	{
		std::string returningString("");
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, path);
		returningString = path;
		std::replace(returningString.begin(), returningString.end(), '\\', '/');
		return returningString;
	}
}