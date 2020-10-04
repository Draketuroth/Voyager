#ifndef VE_TIMING_H
#define VE_TIMING_H

#if defined _WIN64 || defined _WIN32
#include <Windows.h>
#endif

namespace VE 
{
    namespace Core 
    {
        double GetQueryPerformanceMs() {
            static LARGE_INTEGER queryFrequency;
            static BOOL supportsQueryFrequency = QueryPerformanceFrequency(&queryFrequency);

            // Check if installed hardware supports high-resolution counter.
            if (supportsQueryFrequency) {
                LARGE_INTEGER queryCounter;
                QueryPerformanceCounter(&queryCounter);
                return (1000.0 * queryCounter.QuadPart) / queryFrequency.QuadPart;
            }
            else {
                #if _WIN64 
                return static_cast<double>(GetTickCount64());
                #else
                return static_cast<double>(GetTickCount());
                #endif
            }
        }
    }
}

#endif VE_TIMING_H