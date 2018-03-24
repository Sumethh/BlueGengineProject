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
		(void)aArchive;
	}

	ArchiveObject::ArchiveObject(const ArchiveObject&& aArchive)
	{
		(void)aArchive;
	}

	void ArchiveObject::Archive(const char* aValName, const uint32 aValue)
	{
		(void)aValue;
		BlueAssert(false); 
		AssertKeyIsUnique(aValName);		
	}

	void ArchiveObject::Archive(const char* aValName, const glm::vec3& aValue)
	{
		(void)aValue;
		AssertKeyIsUnique(aValName);
		BlueAssert(false);
	}

	void ArchiveObject::Archive(const char* aValName, const glm::quat& aValue)
	{
		(void)aValue;
		AssertKeyIsUnique(aValName);		
		BlueAssert(false);
	}

	void ArchiveObject::Archive(const char* aValName, std::vector<uint32> aArray)
	{
		(void)aArray;
		AssertKeyIsUnique(aValName);
		BlueAssert(false);
	}

	void ArchiveObject::Archive(ArchiveObject* aArchive)
	{
		AssertKeyIsUnique(aArchive->mName.c_str());
		BlueAssert(false);
	}

	void ArchiveObject::Archive(const char* aValName, std::string aValue)
	{
		AssertKeyIsUnique(aValName);
		BlueAssert(false);
	}

	void ArchiveObject::WriteToFile(char* aDir, const char* aFileName)
	{
		std::string path(aDir);
		path.append(aFileName);
		std::ofstream stream;
		stream.open(path, std::ios::out | std::ios::trunc);
		BlueAssert(false);
		stream.close();
	}

	void ArchiveObject::ReadFromFile(const char* aFilePath)
	{
		std::ifstream stream;
		stream.open(aFilePath, std::ios::in);		

		if (!stream.is_open() || stream.bad())
		{
			BlueAssert(false);
		}
		else
		{
			BlueAssert(false);
		}
	}

	void ArchiveObject::AssertKeyIsUnique(const char* aKey) const
	{
		(void)aKey;
	}

}