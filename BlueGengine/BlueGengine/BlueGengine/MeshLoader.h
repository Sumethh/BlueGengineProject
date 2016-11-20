#pragma once
#include "NonCopyable.h"
#include <string>
namespace BlueGengine
{
	class Mesh;
	class MeshLoader : public NonCopyable
	{
		public:

		static Mesh* LoadMeshFromFile(char* aFilePath, std::string aMeshName);
		static Mesh* LoadMeshFromFile(std::string aFilePath, std::string aMeshName, Mesh* aMesh);

		private:
		MeshLoader();
		~MeshLoader();
	};
}
