
#include "Voyager/Core/Timer.h"

namespace VE 
{
    namespace Core 
    {
        Timer::Timer() : _offset(0), _frequency(0)
        {

        }

        Timer::~Timer()
        {

        }

        bool Timer::initTimer()
        {
            std::uint64_t frequency;

            static BOOL supportsQueryFrequency = QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

            if (supportsQueryFrequency)
            {
                _frequency = frequency;
                _offset = getPlatformTimerValue();
                return true;
            }
            // Todo: Find alternative when this fails.
            // else 
            // {
            // 
            // }
            return false;
        }

        std::uint64_t Timer::getPlatformTimerValue()
        {
            std::uint64_t value;
            QueryPerformanceCounter((LARGE_INTEGER*)&value);
            return value;
        }

        std::uint64_t Timer::getPlatformTimerFrequency()
        {
            return _frequency;
        }

        double Timer::getTime()
        {
            return static_cast<double>(getPlatformTimerValue() - _offset) / _frequency;
        }
    }
}