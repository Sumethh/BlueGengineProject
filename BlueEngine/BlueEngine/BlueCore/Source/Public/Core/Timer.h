#pragma once
#include "BlueCore.h"
#include <chrono>

namespace Blue
{
	class Timer
	{
		static_assert(std::chrono::steady_clock::is_steady == true,
					  "The time class requires a steady clock.");

	public:

		void Start()
		{
			start = std::chrono::steady_clock::now();
		}

		//basically the same as start, but wording makes more sense if timer is reused
		void Reset()
		{
			Start();
		}

		long long IntervalMCS()
		{
			using namespace std::chrono;
			auto us = duration_cast<microseconds>(steady_clock::now() - start).count();
			return us;
		}

		double IntervalMS() //return interval in milliseconds
		{
			using namespace std::chrono;
			auto us = duration_cast<microseconds>(steady_clock::now() - start).count();
			return (double)us / (double)1000.0;
		}

		double IntervalS() //return interval in seconds
		{
			return IntervalMS() / 1000.0;
		}
	private:
		std::chrono::steady_clock::time_point start;
	};
}