#include "Bluecore/Utility/Directory.h"
#include "BlueCore/Core/Log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

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

	bool FindFilesInDirectory(std::string aDirectory, std::vector<std::string>& aOutFileNames, EFileFlags aFlags)
	{
		WIN32_FIND_DATA findData;
		LARGE_INTEGER fileSize;
		HANDLE foundResult = INVALID_HANDLE_VALUE;
		DWORD error = 0;
		if (aDirectory.size() > MAX_PATH - 3)
		{
			Log::Error("Directory is too long: " + aDirectory);
			return false;
		}

		foundResult = FindFirstFile(aDirectory.c_str(), &findData);

		if (foundResult == INVALID_HANDLE_VALUE)
		{
			DWORD err = GetLastError();
			Log::Error("Could not find a file in the supplied directory: " + aDirectory);
			return false;
		}
		uint8 fileFlags = ConvertToEFileFlags(findData.dwFileAttributes);
		if (fileFlags & static_cast<uint8>(aFlags))
			aOutFileNames.emplace_back(findData.cFileName);

		DWORD t = FILE_ATTRIBUTE_DIRECTORY;
		DWORD A = FILE_ATTRIBUTE_ARCHIVE;
		while (FindNextFile(foundResult, &findData))
		{
			fileFlags = ConvertToEFileFlags(findData.dwFileAttributes);
			if (fileFlags & static_cast<uint8>(aFlags))
				aOutFileNames.emplace_back(findData.cFileName);
		}
		FindClose(foundResult);
		return aOutFileNames.size() > 0;
	}

	bool Directory::FindAllFilesInDirectory(std::string aDirectory, std::vector<std::string>& aOutFileNames)
	{
		return FindFilesInDirectory(aDirectory, aOutFileNames, EFileFlags::File);
	}

	bool Directory::FindAllFoldersInDirecory(std::string aDirectory, std::vector<std::string>& aOutFileNames)
	{
		return FindFilesInDirectory(aDirectory, aOutFileNames, EFileFlags::Directory);
	}

	std::string Directory::GetWorkingDirectory()
	{
		std::string returningString("");
		char path[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, path);
		returningString = path;
		return returningString;
	}
}