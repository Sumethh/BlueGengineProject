#pragma once
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/Types.h"

#include <future>
#include <functional>

namespace Blue
{
	enum class EThreadType : uint8
	{
		WorkerThread,
		RenderThread,
		PhysicsThread,
		GameThread,
		Count
	};

	namespace TaskSystem
	{
		struct Task
		{
			Task(char* aName, EThreadType aThreadType, bool aSyncedJob = true) : syncedJob(aSyncedJob), name(aName), threadType(aThreadType)
			{

			};

			virtual ~Task()
			{

			};

			virtual void Run() = 0;
			virtual bool IsCompleted() = 0;
			char* name;
			bool syncedJob;
			EThreadType threadType;
		};

		template<typename T>
		Task* CreateTask()
		{
		}

		void Init();
		void Sync();
		void Shutdown();
		void ThreadRun(EThreadType aCurrentThread, const int32 aMillisceondsAlloted = 1000);
		void SubmitTask(Task* aJob);
		std::future<bool> SubmitTrackedTask(Task* aTask);
	}
}
