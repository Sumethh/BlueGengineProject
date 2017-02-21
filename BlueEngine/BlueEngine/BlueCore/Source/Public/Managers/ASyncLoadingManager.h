#pragma once
#include <future>
#include "Managers/UpdateableManager.h"

class AsyncLoadingManager : public UpdatableManager
{
	public:
	struct IAsyncLoadingTracker
	{
		IAsyncLoadingTracker(std::future<bool>&& aOther) : completedFuture(std::move(aOther)) {}
		virtual ~IAsyncLoadingTracker() {};
		virtual void Completed() = 0;

		std::future<bool> completedFuture;
	};

	//Update checks the current status of the loading tasks. Will call Completed() on the loading task when it completes. Will be updated everyframe BEFORE Game::Update. ONLY TO BE UPDATED ON THE MAIN THREAD
	void Update() override;

	static inline AsyncLoadingManager* GI() { if (!mInstance) { mInstance = new AsyncLoadingManager(); } return mInstance; }

	void AddNewTrackingLoadingTask(IAsyncLoadingTracker* aNewTask);


	private:
	static AsyncLoadingManager* mInstance;
};
