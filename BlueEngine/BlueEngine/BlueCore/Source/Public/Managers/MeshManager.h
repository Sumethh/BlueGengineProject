#pragma once
#include "Core/NonCopyable.h"
#include "Core/Types.h"

#include <map>
#include <string>
#include <functional>
#include <future>

struct AsyncLoadingMeshTracker;
namespace BlueCore
{
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
		static inline MeshManager* GI()
		{
			if (!mInstance) { mInstance = new MeshManager; mInstance->LoadDefaultMesh(); }

			return mInstance;
		}
		void AsyncLoadComplete(AsyncLoadingMeshTracker* aDoneLoad);

		private:
		MeshManager();
		~MeshManager();
		void LoadDefaultMesh();
		static MeshManager* mInstance;
		std::map<size_t, StoredMeshData> mMeshList;
	};

}