#pragma once
#include <future>
namespace BlueGengine
{
	namespace AsyncLoadingManager
	{

		struct IAsyncLoadingTracker
		{
			IAsyncLoadingTracker(std::future<bool>&& aOther) : completedFuture(std::move(aOther)) {}
			virtual ~IAsyncLoadingTracker() {};
			virtual void Completed() = 0;

			std::future<bool> completedFuture;
		};

		//Update checks the current status of the loading tasks. Will call Completed() on the loading task when it completes. Will be updated everyframe BEFORE Game::Update. ONLY TO BE UPDATED ON THE MAIN THREAD
		void Update();

		void AddNewTrackingLoadingTask(IAsyncLoadingTracker* aNewTask);


	}
}