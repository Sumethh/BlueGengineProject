#pragma once
#include "Core/Types.h"
#include "../Json/json.hpp"
#include "Core/Defines.h"

#include<glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
namespace BlueCore
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
			return (T)mArchive[aValue];
		}


		nlohmann::json GetArc() { return mArchive; }

		void WriteToFile(char* aDir, const char* aFileName);
		void ReadFromFile(const char* aFilePath);
		std::string str() { return mArchive.dump(0); }
		private:

		inline void AssertKeyIsUnique(const char* key) const
		{
			BlueAssert(mArchive.find(key) == mArchive.end());
		}
		std::string mName;
		nlohmann::json mArchive;
	};
}