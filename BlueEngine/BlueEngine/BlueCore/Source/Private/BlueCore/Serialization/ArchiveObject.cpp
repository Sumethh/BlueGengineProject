#include "BlueCore/Serialization/ArchiveObject.h"
#include "BlueCore/Core/Log.h"

#include <fstream>

namespace Blue
{
	ArchiveObject::ArchiveObject(std::string aName)
	{
		mName = aName;
	}

	ArchiveObject::ArchiveObject(const ArchiveObject& aArchive)
	{

	}

	ArchiveObject::ArchiveObject(const ArchiveObject&& aArchive)
	{

	}

	void ArchiveObject::Archive(const char* aValName, const uint32 aValue)
	{
		AssertKeyIsUnique(aValName);
		mArchive[aValName] = aValue;
	}

	void ArchiveObject::Archive(const char* aValName, const glm::vec3& aValue)
	{
		AssertKeyIsUnique(aValName);
		mArchive[aValName] = { { "x", aValue.x }, { "y", aValue.y }, { "z", aValue.z } };
	}

	void ArchiveObject::Archive(const char* aValName, const glm::quat& aValue)
	{
		AssertKeyIsUnique(aValName);
		mArchive[aValName] = { { "x", aValue.x }, { "y", aValue.y }, { "z", aValue.z }, {"w", aValue.w} };
	}

	void ArchiveObject::Archive(const char* aValName, std::vector<uint32> aArray)
	{
		AssertKeyIsUnique(aValName);
		mArchive[aValName] = aArray;
	}

	void ArchiveObject::Archive(ArchiveObject* aArchive)
	{
		AssertKeyIsUnique(aArchive->mName.c_str());
		mArchive[aArchive->mName] = aArchive->mArchive;
	}

	void ArchiveObject::Archive(const char* aValName, std::string aValue)
	{
		AssertKeyIsUnique(aValName);
		mArchive[aValName] = aValue;
	}

	void ArchiveObject::WriteToFile(char* aDir, const char* aFileName)
	{
		std::string path(aDir);
		path.append(aFileName);
		std::ofstream stream;
		stream.open(path, std::ios::out | std::ios::trunc);
		stream << mArchive.dump(2);
		stream.close();
	}

	void ArchiveObject::ReadFromFile(const char* aFilePath)
	{
		std::ifstream stream;
		stream.open(aFilePath, std::ios::in);
		bool t = stream.is_open();

		if (!stream.is_open() || stream.bad())
		{
			BlueAssert(false);
		}
		else
		{
			mArchive = mArchive.parse(stream);
		}
	}
}