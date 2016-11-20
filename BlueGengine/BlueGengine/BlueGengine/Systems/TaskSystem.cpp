#include "TaskSystem.h"
#include "../Defines.h"
#include "../Types.h"
#include "../Log.h"

#include <MoodyCamel/concurrentqueue.h>

#include <thread>
#include <vector>
#include <string>
#include <atomic>
#define Job_Queue_Size 1000


namespace BlueGengine
{
	namespace TaskSystem
	{
		moodycamel::ConcurrentQueue<ITask*> sJobList;

		std::vector<std::unique_ptr<std::thread>> sThreads;
		std::atomic_bool sRunThreads;
		std::atomic<int> sNumSyncJobs;
		struct TrackedJobWrapper : public ITask
		{
			TrackedJobWrapper(ITask* aJob) : job(aJob) {};
			~TrackedJobWrapper() { promise.set_value(true); delete job; }

			virtual void Run() override { job->Run(); }
			virtual bool IsCompleted() override { return job->IsCompleted(); }
			ITask* job;
			std::promise<bool> promise;
		};

		struct StaticThreadInformation
		{
			uint32 threadID;
		};

		struct ThreadDiagnosticInformation
		{
		};


		void ThreadMain(StaticThreadInformation aInfo)
		{
			while (sRunThreads)
			{
				ITask* job = nullptr;

				if (sJobList.try_dequeue(job))
				{
					BlueAssert(job);

					if (!sRunThreads)
					{
						delete job;
						break;
					}

					job->Run();

					if (job->IsCompleted())
					{
						if (job->syncedJob)
						{
							sNumSyncJobs.fetch_sub(1);
						}

						delete job;
					}
					else
					{
						sJobList.enqueue(job);
					}
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(1));
				}
			}
		}


		void Init()
		{
			uint32 coreCount = std::thread::hardware_concurrency();
			std::string t = "Intializing task system with ";
			t += std::to_string(coreCount);
			t += " task threads";
			LOGI(t.c_str());
			sThreads.reserve(coreCount);
			sRunThreads.store(true);

			for (int i = 0; i < coreCount; ++i)
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

			for (int i = 0; i < sThreads.size(); ++i)
			{
				sThreads[i]->join();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		void SubmitTask(ITask* aTask)
		{
			BlueAssert(aTask);

			if (aTask->syncedJob)
			{
				sNumSyncJobs.fetch_add(1);
			}

			sJobList.enqueue(aTask);
		}

		std::future<bool> SubmitTrackedTask(ITask* aTask)
		{
			BlueAssert(aTask);
			TrackedJobWrapper* newJob = new TrackedJobWrapper(aTask);
			std::future<bool> future = newJob->promise.get_future();

			if (aTask->syncedJob)
			{
				sNumSyncJobs.fetch_add(1);
			}

			sJobList.enqueue(newJob);
			return future;
		}
	}
}