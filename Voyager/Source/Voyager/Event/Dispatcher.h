#ifndef VE_DISPATCHER_H
#define VE_DISPATCHER_H

#include <functional>
#include <vector>
#include <map>

#include "Voyager/Core/Core.h"
#include "Voyager/Event/Event.h"

#include "Voyager/Event/IDispatcher.h"

namespace VE 
{
	namespace Event 
	{
		class VOYAGER_API Dispatcher : public IDispatcher
		{
		public:
			using EventCallbackFn = std::function<void(Event&)>;

			void subscribe(const EventType& descriptor, EventCallbackFn&& slot) 
			{
				_observers[descriptor].push_back(slot);
			}

			void post(Event& event) 
			{
				auto type = event.getEventType();

				// Ignore events for which we do not have observers for
				if (_observers.find(type) == _observers.end()) { return; }

				auto&& observers = _observers.at(type);
				for (auto&& observer : observers) 
				{
					observer(event);
				}
			}
		private:
			std::map<EventType, std::vector<EventCallbackFn>> _observers;
		};
	}
}

#endif