#include "BlueCore/Managers/ASyncLoadingManager.h"
#include <vector>

namespace Blue
{
	AsyncLoadingManager* AsyncLoadingManager::mInstance = nullptr;
	static std::vector<AsyncLoadingManager::AsyncLoadingTracker*> sCurrentLoadingTasks;

	void AsyncLoadingManager::Update()
	{
		for (auto currentTask = sCurrentLoadingTasks.begin(); currentTask != sCurrentLoadingTasks.end();)
		{
			if ((*currentTask)->completedFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
			{
				(*currentTask)->Completed();
				delete (*currentTask);
				currentTask = sCurrentLoadingTasks.erase(currentTask);
			}
			else
			{
				currentTask++;
			}
		}
	}

	void AsyncLoadingManager::AddNewTrackingLoadingTask(AsyncLoadingTracker* aNewTask)
	{
		sCurrentLoadingTasks.push_back(aNewTask);
	}
}