#pragma once
#include "BlueCore/Core/NonCopyable.h"
#include "BlueCore/Core/Types.h"

#include <map>
#include <string>
#include <functional>
#include <future>

namespace Blue
{
	struct AsyncLoadingMeshTracker;

	class Mesh;
	struct AsyncLoadingMeshTracker;
	struct StoredMeshData
	{
		StoredMeshData() : mesh(nullptr), loadingTracker(nullptr)
		{}
		~StoredMeshData();

		Mesh* mesh;
		AsyncLoadingMeshTracker* loadingTracker;
	};


	class MeshManager : NonCopyable
	{
	public:
		Mesh* CreateMesh(std::string meshName);
		Mesh* GetMeshAsync(std::string aMeshName, std::function<void(Mesh*)> aCallback);
		Mesh* GetMesh(std::string aMeshName);
		Mesh* GetMesh(sizeInt aMeshId);

		static inline MeshManager* GI()
		{
			if (!mInstance)
			{
				mInstance = new MeshManager;
				mInstance->LoadDefaultMesh();
			}

			return mInstance;
		}
		void AsyncLoadComplete(AsyncLoadingMeshTracker* aDoneLoad);

	private:
		MeshManager();
		~MeshManager();
		void LoadDefaultMesh();
		static MeshManager* mInstance;
		std::map<sizeInt, StoredMeshData> mMeshList;
	};
}