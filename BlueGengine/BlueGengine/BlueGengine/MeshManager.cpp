#include "MeshManager.h"
#include "Mesh.h"
#include <vector>
#include "MeshLoader.h"
#include "Systems/TaskSystem.h"
#include "Managers/AsyncLoadingMeshTracker.h"
#include "ResourceList.h"
namespace BlueGengine
{
	MeshManager* MeshManager::mInstance = nullptr;

	struct AsyncLoadMeshTask : public TaskSystem::ITask
	{
		AsyncLoadMeshTask(Mesh* aMesh) : TaskSystem::ITask(false), loadingMesh(aMesh)
		{

		}
		virtual void Run() override
		{
			MeshLoader::LoadMeshFromFile(filePath.c_str(), meshName, loadingMesh);
		}
		virtual bool IsCompleted()override { return true; }
		Mesh* loadingMesh;
		std::string filePath;
		std::string meshName;
	};

	MeshManager::MeshManager()
	{
	}

	MeshManager::~MeshManager()
	{
		for (auto& info : mMeshList)
		{
		}

	}

	void MeshManager::LoadDefaultMesh()
	{
		Mesh* sphere = MeshLoader::LoadMeshFromFile("Assets/Models/Sphere.obj", "sphere");
		sphere->UpdateMeshResources();
	}

	void MeshManager::AsyncLoadComplete(AsyncLoadingMeshTracker* aDoneLoad)
	{
		size_t id = aDoneLoad->GetMesh()->GetID();
		delete mMeshList[id].loadingTracker;
		mMeshList[id].loadingTracker = nullptr;
	}

	Mesh* MeshManager::CreateMesh(std::string aMeshName)
	{
		size_t meshId = std::hash<std::string> {}(aMeshName);
		Mesh* newMesh = new Mesh(meshId);
		mMeshList[meshId].mesh = newMesh;
		return newMesh;
	}

	Mesh* MeshManager::GetMeshAsync(std::string aMeshName, std::function<void(Mesh*)> aCallback)
	{
		size_t meshId = std::hash<std::string> {}(aMeshName);
		StoredMeshData& currentMeshData = mMeshList[meshId];

		if (!currentMeshData.mesh)
		{
			Mesh* newMesh = CreateMesh(aMeshName);
			mMeshList[meshId].mesh = newMesh;
			std::string& pathName = sMeshFilePaths[aMeshName];
			AsyncLoadMeshTask* meshLoadingTask = new AsyncLoadMeshTask(newMesh);
			meshLoadingTask->filePath = pathName;
			meshLoadingTask->meshName = aMeshName;
			meshLoadingTask->syncedJob = false;

			AsyncLoadingMeshTracker* newTracker = new AsyncLoadingMeshTracker(std::move(TaskSystem::SubmitTrackedTask(meshLoadingTask)), newMesh);
			AsyncLoadingManager::AddNewTrackingLoadingTask(newTracker);
			currentMeshData.loadingTracker = newTracker;
			newTracker->AddCallback(aCallback);
		}
		else if (currentMeshData.loadingTracker)
		{
			currentMeshData.loadingTracker->AddCallback(aCallback);
		}
		else
		{
			return currentMeshData.mesh;
		}

		return GetMesh("sphere");

	}
	Mesh* MeshManager::GetMesh(std::string aMeshName)
	{
		uint64 id = std::hash<std::string> {}(aMeshName);
		return mMeshList[id].mesh;
	}




	StoredMeshData::~StoredMeshData()
	{
		{
			delete mesh;

			if (loadingTracker)
			{
				delete loadingTracker;
			}
		}
	}

}