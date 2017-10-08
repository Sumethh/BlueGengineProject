#pragma once
#include <string>

namespace Blue
{
	struct FileInfo
	{
		std::string path;
		std::string fileName;
		std::string extension;
	};

	/*  class File
	    {
	    public:

		static File LoadFile(std::string aPath);

		std::string GetName();
		std::string GetExtension();

	    private:
		std::string mFileName;
		std::string mExtension;
	    };*/
}