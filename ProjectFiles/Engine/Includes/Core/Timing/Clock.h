//============================================================================
// # VOYAGER ENGINE #
// Name: Clock.h
// Module: Core
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Custom Voyager clock system for delta time and profiling
//============================================================================

#ifndef VE_CORE_TIMING_CLOCK_H
#define VE_CORE_TIMING_CLOCK_H

// Necessary evil. Remove if possible.
#include <Windows.h>

namespace Timing
{
	class __declspec(dllexport) Clock
	{
	private:
		LARGE_INTEGER _time_frequency;
		LARGE_INTEGER _last_start_time;
		LARGE_INTEGER _delta_last_lap;
		float _delta_time;
	public:
		bool initialize();
		bool shutdown();
		void start();
		void stop();
		void lap(); 

		// Delta distance in time between the frames.
		float lastLapTime() const;
	};
}


#endif