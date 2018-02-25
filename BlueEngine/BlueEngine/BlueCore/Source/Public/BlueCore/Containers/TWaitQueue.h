#include "BlueCore/BlueCore.h"

#include <queue>
#include <mutex>
#include <condition_variable>

namespace Blue
{
	template<typename T>
	class TWaitQueue
	{
	public:
		void Push(T aItem)
		{
			std::lock_guard<std::mutex> lock(mMutex);
			mQueue.push(aItem);
			mCondition.notify_one();
		}

		bool WaitAndPop(T& aOutItem, const uint32 aMsToWait = 10)
		{
			std::unique_lock<std::mutex> lock(mMutex);
			mCondition.wait_for(lock, std::chrono::milliseconds(aMsToWait), [this]()
			{
				return !mQueue.empty();
			});
			if (mQueue.size())
			{
				aOutItem = mQueue.front();
				mQueue.pop();
				return true;
			}
			return false;
		}

		bool LockPop(T& aOutItem)
		{
			std::lock_guard<std::mutex> lock(mMutex);
			if (mQueue.empty())
				return false;
			aOutItem = mQueue.front();
			mQueue.pop();
			return true;
		}

		void NotifyAllWaiting()
		{
			mCondition.notify_all();
		}
	private:
		std::mutex mMutex;
		std::condition_variable mCondition;
		std::queue<T> mQueue;
		bool mCanWait;
	};
}