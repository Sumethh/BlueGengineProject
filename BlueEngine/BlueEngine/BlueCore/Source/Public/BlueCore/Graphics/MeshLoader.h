#pragma once
#include "BlueCore/Core/NonCopyable.h"
#include <string>

namespace Blue
{
	class Mesh;
	class MeshLoader : public NonCopyable
	{
	public:

		static void LoadMeshFromFile(std::string aFilePath, std::string aMeshName, Mesh* aOutMesh);

	private:
		MeshLoader();
		~MeshLoader();
	};
}