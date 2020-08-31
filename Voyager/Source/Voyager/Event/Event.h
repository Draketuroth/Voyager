#ifndef VE_EVENT_H
#define VE_EVENT_H

#include <string>
#include <functional>
#include <memory>
#include <ostream>

#include "Voyager/Core/Core.h"

namespace VE
{
	namespace Event
	{
		const enum class EventType
		{
			NONE = 0,
			VE_KEY_PRESSED,
			VE_KEY_RELEASED,
			VE_KEY_TYPED,

			VE_MOUSE_MOVED,
			VE_MOUSE_SCROLLED,
			VE_MOUSE_ENTERED,
			VE_MOUSE_LEAVED,
			VE_MOUSE_PRESSED,
			VE_MOUSE_RELEASED,

			VE_APP_TICK,
			VE_APP_UPDATE,
			VE_APP_RENDER,

			VE_WINDOW_RESIZE,
			VE_WINDOW_REFRESH,
			VE_WINDOW_CLOSE,
			VE_WINDOW_FOCUS,
			VE_WINDOW_LOST_FOCUS,
			VE_WINDOW_MOVED,

			VE_ENTITY_DESTROYED,
			VE_ENTITY_CREATED,

			VE_COMPONENT_ADDED,
			VE_COMPONENT_REMOVED,

			VE_FILE_CREATED,
			VE_FILE_MODIFIED,
			VE_FILE_DELETED
		};

		const enum EventCategory
		{
			VE_NONE = 0,
			VE_APPLICATION = BIT(0),
			VE_INPUT = BIT(1),
			VE_KEYBOARD = BIT(2),
			VE_MOUSE = BIT(3),
			VE_MOUSEBUTTON = BIT(4),
			VE_ENTITY = BIT(5),
			VE_COMPONENT = BIT(6),
			VE_FILE = BIT(7)
		};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType(){return EventType::##type; }\
																virtual EventType getEventType() const override {return getStaticType(); }\
																virtual const char* getName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

		class VOYAGER_API Event
		{
		public:
			bool handled = false;

			virtual EventType getEventType() const = 0;
			virtual const char* getName() const = 0;
			virtual int getCategoryFlags() const = 0;
			virtual std::string toString() const { return getName(); };

			inline bool isInCategory(EventCategory category)
			{
				return getCategoryFlags() & category;
			}
		};

		class EventHandler
		{
			template <class T>
			using EventFn = std::function<bool(T&)>;
		public:
			EventHandler(Event& event) : _event(event) {}

			template<typename T>
			bool execute(EventFn<T> func)
			{
				if (_event.getEventType() == T::getStaticType())
				{
					_event.handled = func(*(T*)& _event);
					return true;
				}
				return false;
			}
		private:
			Event& _event;
		};

		inline std::ostream& operator<<(std::ostream& os, const Event& e)
		{
			return os << e.toString();
		}
	}
}

#endif