#include "BlueCore/Managers/MeshManager.h"
#include "BlueCore/Managers/MemoryManager.h"
#include "BlueCore/Graphics/Mesh.h"
#include "BlueCore/Graphics/MeshLoader.h"
#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Managers/AsyncLoadingMeshTracker.h"
#include "BlueCore/Core/ResourceList.h"
#include "BlueCore/Core/Timer.h"
#include "BlueCore/Core/Log.h"

#include "BlueCore/Tasks/UpdateGraphicsResourceTask.h"

#include <vector>

namespace Blue
{
	MeshManager* MeshManager::mInstance = nullptr;

	struct AsyncLoadMeshTask : public TaskSystem::Task
	{
		AsyncLoadMeshTask(Mesh* aMesh) : TaskSystem::Task("Async Mesh Load", EThreadType::WorkerThread, false), loadedMesh(aMesh)
		{

		}
		virtual void Run() override
		{
			Timer loadingTimer;
			loadingTimer.Start();
			MeshLoader::LoadMeshFromFile(filePath.c_str(), meshName, loadedMesh);
			Log::Info(Logger("Finished loading mesh") << meshName << " in " << loadingTimer.IntervalMS() << " ms");
		}

		virtual bool IsCompleted()override
		{
			return true;
		}

		Mesh* loadedMesh;
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
		Mesh* sphere = CreateMesh("sphere");
		MeshLoader::LoadMeshFromFile("Assets/Models/Sphere.obj", "sphere", sphere);
		sphere->QueueResourceUpdate();
	}

	void MeshManager::AsyncLoadComplete(AsyncLoadingMeshTracker* aDoneLoad)
	{
		uint64 id = aDoneLoad->GetMeshID();
		StoredMeshData& finishedAsync = mMeshList[id];
		finishedAsync.loadingTracker = nullptr;

		UpdateGraphicsResourceTask* updateResourceTask = new UpdateGraphicsResourceTask();
		updateResourceTask->graphicsResourceToUpdate = mMeshList[id].mesh;
		TaskSystem::SubmitTask(updateResourceTask);
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
		sizeInt meshId = std::hash<std::string> {}(aMeshName);
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

			AsyncLoadingMeshTracker* newTracker = new AsyncLoadingMeshTracker(std::move(TaskSystem::SubmitTrackedTask(meshLoadingTask)), meshId);
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

	Blue::Mesh* MeshManager::GetMesh(sizeInt aMeshId)
	{
		if (mMeshList.find(aMeshId) != mMeshList.end())
		{
			return mMeshList[aMeshId].mesh;
		}
		return nullptr;
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