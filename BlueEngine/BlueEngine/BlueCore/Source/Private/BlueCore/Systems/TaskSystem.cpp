#include "BlueCore/Systems/TaskSystem.h"
#include "BlueCore/Core/Defines.h"
#include "BlueCore/Core/Types.h"
#include "BlueCore/Core/Log.h"
#include "BlueCore/Containers/TWaitQueue.h"
#include "BlueCore/Core/Timer.h"

#include <thread>
#include <shared_mutex>

#include <map>
#include <string>
#include <atomic>
#define Job_Queue_Size 1000


namespace Blue
{
	namespace TaskSystem
	{
		//moodycamel::ConcurrentQueue<ITask*> sJobList;
		//TWaitQueue<Task*> sJobList;
		std::vector<std::unique_ptr<std::thread>> sThreads;
		std::atomic_bool sRunThreads;
		std::atomic<int> sNumSyncJobs;

		TWaitQueue<Task*> sThreadJobList[static_cast<int32>(EThreadType::Count)];


		struct TrackedJobWrapper : public Task
		{
			TrackedJobWrapper(Task* aJob) : Task("TrackedJobWrapper", aJob->threadType), job(aJob) {};
			~TrackedJobWrapper()
			{
				promise.set_value(true);
				delete job;
			}

			virtual void Run() override
			{
				job->Run();
			}
			virtual bool IsCompleted() override
			{
				return job->IsCompleted();
			}
			Task* job;
			std::promise<bool> promise;
		};

		struct StaticThreadInformation
		{
			uint32 threadID = 0;
			EThreadType threadType = EThreadType::WorkerThread;
			std::string threadName = "Worker Thread";
		};

		struct ThreadDiagnosticInformation
		{

		};

		void ThreadMain(StaticThreadInformation aInfo)
		{
			while (sRunThreads)
			{
				ThreadRun(aInfo.threadType);
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}


		void Init()
		{
			uint32 coreCount = std::thread::hardware_concurrency() / 2;

			std::string t = "Intializing task system with ";
			t += std::to_string(coreCount);
			t += " task threads";
			Log::Info(t);
			sThreads.reserve(coreCount);
			sRunThreads.store(true);

			for (uint32 i = 0; i < coreCount; ++i)
			{
				StaticThreadInformation info;
				info.threadID = i;
				sThreads.push_back(std::make_unique<std::thread>(ThreadMain, info));
			}
		}

		void Sync()
		{
			while (sNumSyncJobs.load() > 0)
			{
				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		}

		void Shutdown()
		{
			sRunThreads.store(false);
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			for (uint32 i = 0; i < static_cast<uint32>(EThreadType::Count); ++i)
			{
				sThreadJobList[i].NotifyAllWaiting();
			}
			for (size_t i = 0; i < sThreads.size(); ++i)
			{
				sThreads[i]->join();
			}

			Task* remainingTask = nullptr;


			for (int32 index = 0; index < static_cast<int32>(EThreadType::Count); ++index)
			{
				while (sThreadJobList[index].LockPop(remainingTask))
				{
					Log::Info(Logger("Deleting Task ") << remainingTask->name);
					delete remainingTask;
				}
			}
		}

		void ThreadRun(EThreadType aCurrentThread, const int32 aMiliSecondsAlloted)
		{
			Timer timeRunning;
			timeRunning.Start();

			if (aCurrentThread >= EThreadType::Count)
			{
				Log::Error("Thread tried to run with incorrect thread type");
				return;
			}

			while (timeRunning.IntervalMS() < aMiliSecondsAlloted)
			{
				Task* currentTask = nullptr;

				if (!sThreadJobList[static_cast<int32>(aCurrentThread)].WaitAndPop(currentTask))
					break;
				else
					currentTask->Run();

				if (currentTask->IsCompleted())
				{
					if (currentTask->syncedJob)
						sNumSyncJobs.fetch_sub(1);

					delete currentTask;
				}
				else
				{
					sThreadJobList[static_cast<int32>(aCurrentThread)].Push(currentTask);
				}
			}
		}

		void SubmitTask(Task* aTask)
		{
			BlueAssert(aTask);

			if (aTask->syncedJob)
			{
				sNumSyncJobs.fetch_add(1);
			}

			sThreadJobList[static_cast<int32>(aTask->threadType)].Push(aTask);
		}

		std::future<bool> SubmitTrackedTask(Task* aTask)
		{
			BlueAssert(aTask);
			TrackedJobWrapper* newJob = new TrackedJobWrapper(aTask);
			std::future<bool> future = newJob->promise.get_future();

			if (aTask->syncedJob)
			{
				sNumSyncJobs.fetch_add(1);
			}

			sThreadJobList[static_cast<int32>(aTask->threadType)].Push(newJob);
			return future;
		}
	}
}