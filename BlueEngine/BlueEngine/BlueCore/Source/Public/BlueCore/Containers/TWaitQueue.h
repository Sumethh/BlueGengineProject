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

		bool WaitAndPop(T& aOutItem)
		{
			std::unique_lock<std::mutex> lock(mMutex);
			mCondition.wait(lock, [this]()
			{
				return !mQueue.empty();
			});

			aOutItem = mQueue.front();
			mQueue.pop();
			return true;
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
	private:
		std::mutex mMutex;
		std::condition_variable mCondition;
		std::queue<T> mQueue;
	};
}