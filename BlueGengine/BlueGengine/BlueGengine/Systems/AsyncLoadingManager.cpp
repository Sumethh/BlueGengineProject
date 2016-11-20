#include "ASyncLoadingManager.h"
#include <vector>

namespace BlueGengine
{
	namespace AsyncLoadingManager
	{
		static std::vector<IAsyncLoadingTracker*> sCurrentLoadingTasks;


		void Update()
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

		void AddNewTrackingLoadingTask(IAsyncLoadingTracker* aNewTask)
		{
			sCurrentLoadingTasks.push_back(aNewTask);
		}

	}
}