#ifndef VE_CORE_H
#define VE_CORE_H

#include <memory>

#ifdef VE_PLATFORM_WINDOWS
	#ifdef VE_BUILD_DLL	
		#define VOYAGER_API  __declspec(dllexport)
	#else
		#define VOYAGER_API  __declspec(dllimport)
	#endif
#else
	#error Voyager only supported at the moment!
#endif

#ifdef VE_DEBUG
	#define VE_ENABLE_ASSERTS
#endif

#ifdef VE_ENABLE_ASSERTS
	#define VE_ASSERT(x, ...) {if(!(x)) {VE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define VE_CORE_ASSERT(x, ...) {if(!(x)) {VE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define VE_ASSERT(x, ...)
#define VE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define VE_BIND_EVENT(fn) std::bind(&fn, this, std::placeholders::_1)

namespace VE 
{
	namespace Core 
	{
		template<typename T>
		using Scope = std::unique_ptr<T>;

		template<typename T>
		using Ref = std::shared_ptr<T>;
	}
}

#endif
