#pragma once
#include <future>
#include "BlueCore/Managers/UpdateableManager.h"

namespace Blue
{
	class AsyncLoadingManager : public UpdatableManager
	{
	public:
		struct AsyncLoadingTracker
		{
			AsyncLoadingTracker(std::future<bool>&& aOther) : completedFuture(std::move(aOther)) {}
			virtual ~AsyncLoadingTracker() {};
			virtual void Completed() = 0;

			std::future<bool> completedFuture;
		};

		//Update checks the current status of the loading tasks. Will call Completed() on the loading task when it completes. Will be updated everyframe BEFORE Game::Update. ONLY TO BE UPDATED ON THE MAIN THREAD
		void Update() override;

		static inline AsyncLoadingManager* GI()
		{
			if (!mInstance)
			{
				mInstance = new AsyncLoadingManager();
			}
			return mInstance;
		}

		void AddNewTrackingLoadingTask(AsyncLoadingTracker* aNewTask);

	private:
		static AsyncLoadingManager* mInstance;
	};
}