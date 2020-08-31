#ifndef VE_IDISPATCHER_H
#define VE_IDISPATCHER_H

#include "Voyager/Core/Core.h"

#include <string>

namespace VE { namespace Event { class Dispatcher; } }
namespace VE { namespace IO { class FileNotifier; } }

namespace VE
{
	namespace Event
	{
		class VOYAGER_API IDispatcher
		{
		public:
			virtual ~IDispatcher() = default;

			static Dispatcher* create();
		};
	}

	namespace IO 
	{
		class VOYAGER_API IFileNotifier
		{
		public:
			virtual ~IFileNotifier() = default;

			static FileNotifier* create(std::string baseFolderPath, Core::Scope<Event::Dispatcher> dispatcher);
		};
	}
}

#endif
