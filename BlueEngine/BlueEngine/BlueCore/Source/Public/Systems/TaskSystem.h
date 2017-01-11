#pragma once
#include "Core/Defines.h"
#include <future>
#include <functional>
namespace BlueCore
{
	namespace TaskSystem
	{

		struct BLUECORE_API ITask
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

		BLUECORE_API void Init();
		BLUECORE_API void Sync();
		BLUECORE_API void Shutdown();

		BLUECORE_API void SubmitTask(ITask* aJob);
		std::future<bool> SubmitTrackedTask(ITask* aTask);
	}
}
