#ifndef VE_LOG_H
#define VE_LOG_H

#include <memory>

#include "Voyager/Core/Core.h"
#include <spdlog/spdlog.h>

namespace VE
{
	namespace Core 
	{
		class VOYAGER_API Log
		{
		public:
			static void init();

			inline static Ref<spdlog::logger>& getCoreLogger() { return _coreLogger; }
			inline static Ref<spdlog::logger>& getClientLogger() { return _clientLogger; }

		private:
			static Ref<spdlog::logger> _coreLogger;
			static Ref<spdlog::logger> _clientLogger;
		};
	}
};

// Core log macros
#define VE_CORE_TRACE(...) ::VE::Core::Log::getCoreLogger()->trace(__VA_ARGS__)
#define VE_CORE_INFO(...)  ::VE::Core::Log::getCoreLogger()->info(__VA_ARGS__)
#define VE_CORE_WARN(...)  ::VE::Core::Log::getCoreLogger()->warn(__VA_ARGS__)
#define VE_CORE_ERROR(...) ::VE::Core::Log::getCoreLogger()->error(__VA_ARGS__)
#define VE_CORE_FATAL(...) ::VE::Core::Log::getCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define VE_TRACE(...) ::VE::Core::Log::getClientLogger()->trace(__VA_ARGS__)
#define VE_INFO(...)  ::VE::Core::Log::getClientLogger()->info(__VA_ARGS__)
#define VE_WARN(...)  ::VE::Core::Log::getClientLogger()->warn(__VA_ARGS__)
#define VE_ERROR(...) ::VE::Core::Log::getClientLogger()->error(__VA_ARGS__)
#define VE_FATAL(...) ::VE::Core::Log::getClientLogger()->fatal(__VA_ARGS__)

#endif