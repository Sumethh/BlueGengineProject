#include "Managers/MeshManager.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshLoader.h"
#include "Systems/TaskSystem.h"
#include "Managers/AsyncLoadingMeshTracker.h"
#include "Core/ResourceList.h"
#include <vector>

MeshManager* MeshManager::mInstance = nullptr;

struct AsyncLoadMeshTask : public TaskSystem::ITask

{
	AsyncLoadMeshTask(Mesh* aMesh) : TaskSystem::ITask("Async Mesh Loading Task", false), loadingMesh(aMesh)
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
	//TODO: Look if anything needs cleaning
}

void MeshManager::LoadDefaultMesh()
{
	Mesh* sphere = MeshLoader::LoadMeshFromFile("Assets/Models/Sphere.obj", "sphere");

	if (sphere == nullptr)
	{
		return;
	}

	sphere->UpdateMeshResources();
}

void MeshManager::AsyncLoadComplete(AsyncLoadingMeshTracker* aDoneLoad)
{
	uint64 id = aDoneLoad->GetMesh()->GetID();
	StoredMeshData& finishedAsync = mMeshList[id];
	finishedAsync.loadingTracker = nullptr;
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
		AsyncLoadingManager::GI()->AddNewTrackingLoadingTask(newTracker);
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
