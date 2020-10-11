#ifndef VE_TIMER_H
#define VE_TIMER_H

#if defined _WIN64 || defined _WIN32
#define NOMINMAX
#include <Windows.h>
#endif

#include <cstdint>

namespace VE 
{
    namespace Core 
    {
        class Timer 
        {
        public:
            Timer();
            ~Timer();

            bool initTimer();

            std::uint64_t getPlatformTimerValue();

            std::uint64_t getPlatformTimerFrequency();

            double getTime();

        private:
            Timer(const Timer&);
            Timer& operator=(const Timer&);

            std::uint64_t _offset;
            std::uint64_t _frequency;
        };
    }
}

#endif VE_TIMING_H