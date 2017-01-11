#include "Managers/ASyncLoadingManager.h"
#include <vector>

namespace BlueCore
{
	AsyncLoadingManager* AsyncLoadingManager::mInstance = nullptr;
	static std::vector<AsyncLoadingManager::IAsyncLoadingTracker*> sCurrentLoadingTasks;


	void AsyncLoadingManager::Update()
	{
		for (auto currentTask = sCurrentLoadingTasks.begin(); currentTask != sCurrentLoadingTasks.end();)
		{
			if ((*currentTask)->completedFuture._Is_ready())
			{
				(*currentTask)->Completed();
				delete(*currentTask);
				currentTask = sCurrentLoadingTasks.erase(currentTask);
			}
			else
			{
				currentTask++;
			}
		}
	}

	void AsyncLoadingManager::AddNewTrackingLoadingTask(IAsyncLoadingTracker* aNewTask)
	{
		sCurrentLoadingTasks.push_back(aNewTask);
	}


}