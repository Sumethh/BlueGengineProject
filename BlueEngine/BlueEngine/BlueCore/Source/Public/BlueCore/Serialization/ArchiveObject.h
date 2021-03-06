#pragma once
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Defines.h"

#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>
namespace Blue
{
	class ArchiveObject
	{
	public:
		ArchiveObject(std::string aName);
		ArchiveObject(const ArchiveObject& aArchive);
		ArchiveObject(const ArchiveObject&& aArchive);

		void Archive(const char* aValName, const uint32 aValue);
		void Archive(const char* aValName, const glm::vec3& aValue);
		void Archive(const char* aValName, const glm::quat& aValue);
		void Archive(const char* aValName, std::vector<uint32> aArray);
		void Archive(const char* aValName, std::string aValue);
		void Archive(ArchiveObject* aArchive);

		template<typename T>
		T Restore(const std::string aValue)
		{
			BlueAssert(false);
		}

		void WriteToFile(char* aDir, const char* aFileName);
		void ReadFromFile(const char* aFilePath);

		std::string str()
		{
			BlueAssert(false);
		}

	private:
		void AssertKeyIsUnique(const char* aKey) const;
		std::string mName;
	};
}