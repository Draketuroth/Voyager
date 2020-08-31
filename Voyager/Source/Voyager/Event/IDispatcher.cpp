
#include "Voyager/Event/IDispatcher.h"
#include "Voyager/Event/Dispatcher.h"
#include "Voyager/IO/FileNotifier.h"

namespace VE
{
	namespace Event
	{
		Dispatcher* IDispatcher::create()
		{
			return new Dispatcher();
		}
	}

	namespace IO
	{
		FileNotifier* IFileNotifier::create(std::string baseFolderPath, Core::Scope<Event::Dispatcher> dispatcher)
		{
			return new FileNotifier(baseFolderPath, std::move(dispatcher));
		}
	}
}
