#include "Bluecore/Utility/Directory.h"
#include "BlueCore/Core/Log.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <algorithm>
namespace Blue
{

	enum class EFileFlags : uint8
	{
		Directory = BlueBit(1),
		File = BlueBit(2)
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

	bool _FindFilesInDirectory(std::string aDirectory, std::vector<FileInfo>& aOutFileNames, EFileFlags aFlags)
	{
		WIN32_FIND_DATA findData;
		HANDLE foundResult = INVALID_HANDLE_VALUE;
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
			Log::Error("Could not find a file in the supplied directory: " + aDirectory);
			return false;
		}

		if (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN || findData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY)
			return true;

		uint8 fileFlags = ConvertToEFileFlags(findData.dwFileAttributes);

		auto flags = findData.dwFileAttributes;
		flags &= ~FILE_ATTRIBUTE_ARCHIVE;
		flags &= ~FILE_ATTRIBUTE_DIRECTORY;

		FileInfo currentFileInfo{};

		if (fileFlags & static_cast<uint8>(aFlags))
		{
			std::string fullFileName(findData.cFileName);
			sizeInt extensionLocation = fullFileName.find_first_of('.');
			currentFileInfo.path = aDirectory + fullFileName;
			if (fileFlags & static_cast<uint8>(EFileFlags::Directory))
				currentFileInfo.path += "/";

			currentFileInfo.fileName = fullFileName.substr(0, extensionLocation);
			currentFileInfo.extension = fullFileName.substr(extensionLocation + 1, fullFileName.size() - extensionLocation - 1);
			aOutFileNames.emplace_back(currentFileInfo);
		}

		while (FindNextFile(foundResult, &findData))
		{
			fileFlags = ConvertToEFileFlags(findData.dwFileAttributes);
			flags = findData.dwFileAttributes;
			flags &= ~FILE_ATTRIBUTE_ARCHIVE;
			flags &= ~FILE_ATTRIBUTE_DIRECTORY;
			if (fileFlags & static_cast<uint8>(aFlags))
			{
				currentFileInfo = {};
				std::string fullFileName(findData.cFileName);
				sizeInt extensionLocation = fullFileName.find_first_of('.');
				currentFileInfo.path = aDirectory + fullFileName;
				if (fileFlags & static_cast<uint8>(EFileFlags::Directory))
					currentFileInfo.path += "/";

				currentFileInfo.fileName = fullFileName.substr(0, extensionLocation);
				currentFileInfo.extension = fullFileName.substr(extensionLocation + 1, fullFileName.size() - extensionLocation - 1);
				aOutFileNames.emplace_back(currentFileInfo);
			}
		}
		FindClose(foundResult);
		return aOutFileNames.size() > 0;
	}

	bool _DoesDirectoryExist(const std::string& aDirectory)
	{
		DWORD fileAttribues = GetFileAttributesA(aDirectory.c_str());

		if (fileAttribues & FILE_ATTRIBUTE_DIRECTORY)
			return true;

		return false;
	}

	bool _FindAllFilesInDirectoryAndSubDirectories(const std::string& aDirectory, std::vector<FileInfo>& OutFileInfo)
	{
		std::vector<FileInfo> subDirectories;
		if (_FindFilesInDirectory(aDirectory, subDirectories, EFileFlags::Directory))
		{
			static std::string defaultFoldersToIgnore = ".";
			for (const FileInfo& info : subDirectories)
			{
				//TODO: Figure out why we are finding files . and ..
				if (!info.fileName.size() || info.fileName == defaultFoldersToIgnore)
					continue;
				_FindAllFilesInDirectoryAndSubDirectories(info.path, OutFileInfo);
			}
		}
		_FindFilesInDirectory(aDirectory, OutFileInfo, EFileFlags::File);
		return OutFileInfo.size();
	}

	bool Directory::FindAllFilesInDirectory(const std::string& aDirectory, std::vector<FileInfo>& aOutFileNames)
	{
		return _FindFilesInDirectory(aDirectory, aOutFileNames, EFileFlags::File);
	}

	bool Directory::FindAllFilesInDirectoryAndSubDirectories(const std::string& aDirectory, std::vector<FileInfo>& OutFileInfo)
	{
		return _FindAllFilesInDirectoryAndSubDirectories(aDirectory, OutFileInfo);
	}

	bool Directory::FindAllFoldersInDirectory(const std::string& aDirectory, std::vector<FileInfo>& aOutFileNames)
	{
		return _FindFilesInDirectory(aDirectory, aOutFileNames, EFileFlags::Directory);
	}

	bool Directory::DoesDirectoryExist(const std::string& aDirectory)
	{
		return _DoesDirectoryExist(aDirectory);
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