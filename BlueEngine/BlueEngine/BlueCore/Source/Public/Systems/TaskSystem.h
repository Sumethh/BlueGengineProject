#pragma once
#include "Core/Defines.h"
#include <future>
#include <functional>

namespace Blue
{
	namespace TaskSystem
	{

		struct ITask
		{
			ITask(char* aName, bool aSyncedJob = true) : syncedJob(aSyncedJob), name(aName)
			{

			};

			virtual ~ITask()
			{

			};

			virtual void Run() = 0;
			virtual bool IsCompleted() = 0;
			char* name;
			bool syncedJob;
		};

		void Init();
		void Sync();
		void Shutdown();

		void SubmitTask(ITask* aJob);
		std::future<bool> SubmitTrackedTask(ITask* aTask);
	}
}
