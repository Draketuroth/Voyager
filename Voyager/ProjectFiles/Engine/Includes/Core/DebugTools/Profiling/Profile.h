#ifndef VE_CORE_DEBUG_PROFILE_H
#define VE_CORE_DEBUG_PROFILE_H
#if PROFILING_ON
#include <Core\Timing\Clock.h>
#endif

namespace Profiling
{
	class __declspec(dllexport) Profile
	{
#if PROFILING_ON
		const char* category;
		Timing::Clock clock;
#endif // PROFILING_ON
	public:
#if PROFILING_ON
		Profile(const char* category);
		~Profile();
#else
		Profile(const char* category) {}
		~Profile() {}
#endif // PROFILING_ON
	};
}

#if PROFILING_ON
#define PROFILE(category) Profiling::Profile p(category);
#else
#define PROFILE(category)
#endif // PROFILING_ON

#endif
