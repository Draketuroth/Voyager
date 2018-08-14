/*
* Profile.cpp
* Helper class for profiler
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#if PROFILING_ON
#include "Profile.h"
#include <Core\DebugTools\Profiling\Profiler.h>

namespace Profiling
{
	Profile::Profile(const char* category) : category(category)
	{
		clock.initialize();
		clock.start();
	}
	Profile::~Profile()
	{
		clock.stop();
		profiler.addEntry(category, clock.lastLapTime());
	}
}

#endif