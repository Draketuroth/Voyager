#include "Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace VE
{
	namespace Core 
	{
		Ref<spdlog::logger> Log::_coreLogger;
		Ref<spdlog::logger> Log::_clientLogger;

		void Log::init()
		{
			// Time stamp | Logger | Message
			spdlog::set_pattern("%^[%T] %n: %v%$");
			_coreLogger = spdlog::stdout_color_mt("VOYAGER");
			_coreLogger->set_level(spdlog::level::trace);

			_clientLogger = spdlog::stdout_color_mt("APP");
			_clientLogger->set_level(spdlog::level::trace);
		}
	}
};