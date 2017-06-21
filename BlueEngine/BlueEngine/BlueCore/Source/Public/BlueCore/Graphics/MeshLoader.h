#pragma once
#include "BlueCore/Core/NonCopyable.h"
#include <string>

namespace Blue
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