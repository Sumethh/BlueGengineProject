#pragma once
#include <future>
#include <functional>
namespace BlueGengine
{
	namespace TaskSystem
	{

		struct ITask
		{
			ITask(bool aSyncedJob = true) : syncedJob(aSyncedJob)
			{

			};

			virtual ~ITask()
			{

			};

			virtual void Run() = 0;
			virtual bool IsCompleted() = 0;

			bool syncedJob;
		};

		void Init();
		void Sync();
		void Shutdown();

		void SubmitTask(ITask* aJob);
		std::future<bool> SubmitTrackedTask(ITask* aTask);
	}
}
