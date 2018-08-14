/*
* Clock.cpp
* Default clock system for delta time and profiling
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <Core\Timing\Clock.h>

namespace Timing
{

	bool Clock::initialize()
	{
		// Number of clock ticks we are getting per second.
		// Will not ever change until only the computer is rebooted.
		// Chances are it will still be the same after reboot. 
		bool b = QueryPerformanceFrequency(&_time_frequency) != 0;
		if (!b)
		{
			return false;
		}
		return QueryPerformanceCounter(&_last_start_time) != 0;
	}

	bool Clock::shutdown()
	{ 
		return true; 
	}

	void Clock::start()
	{
		QueryPerformanceCounter(&_last_start_time);
	}
	void Clock::stop()
	{
		LARGE_INTEGER this_time;
		QueryPerformanceCounter(&this_time);
		LARGE_INTEGER delta;
		delta.QuadPart = this_time.QuadPart - _last_start_time.QuadPart;
		_delta_time = ((float)delta.QuadPart) / _time_frequency.QuadPart;
		_delta_last_lap.QuadPart = this_time.QuadPart;
	}

	void Clock::lap()
	{
		stop();
		start();
	}

	float Clock::lastLapTime() const
	{
		return _delta_time;
	}

}