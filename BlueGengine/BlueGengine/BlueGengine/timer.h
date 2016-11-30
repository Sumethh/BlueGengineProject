#pragma once

#include <chrono>

class Timer
{
	using Clock = std::chrono::steady_clock;
	using Tick = Clock::time_point;
	static_assert(Clock::is_steady == true ,
				  "The time class requires a steady clock.");

	public:

	void Start()
	{
		start = Clock::now();
	}

	//basically the same as start, but wording makes more sense if timer is reused
	void Reset() { Start(); }

	long long IntervalMCS()
	{
		using namespace std::chrono;
		auto us = duration_cast<microseconds>(Clock::now() - start).count();
		return us;
	}

	double IntervalMS() //return interval in milliseconds
	{
		using namespace std::chrono;
		auto us = duration_cast<microseconds>(Clock::now() - start).count();
		return (double)us / (double)1000.0;
	}

	double IntervalS() //return interval in seconds
	{
		return IntervalMS() / 1000.0;
	}
	private:
	Tick start;
};
