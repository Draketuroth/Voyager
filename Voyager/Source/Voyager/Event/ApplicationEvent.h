#ifndef VE_APPLICATIONEVENT_H
#define VE_APPLICATIONEVENT_H

#include <sstream>

#include "Voyager/Event/Event.h"

namespace VE
{
	namespace Event
	{
		class VOYAGER_API WindowResizeEvent : public Event
		{
		public:
			WindowResizeEvent(unsigned int width, unsigned int height) : _width(width), _height(height) {}

			inline unsigned int getWidth() const { return _width; }
			inline unsigned int getHeight() const { return _height; }

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "WindowResizeEvent: " << _width << ", " << _height;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_WINDOW_RESIZE)
				EVENT_CLASS_CATEGORY(VE_APPLICATION)

		private:
			unsigned int _width;
			unsigned int _height;
		};

		class VOYAGER_API WindowCloseEvent : public Event
		{
		public:
			WindowCloseEvent() {}

			EVENT_CLASS_TYPE(VE_WINDOW_CLOSE)
				EVENT_CLASS_CATEGORY(VE_APPLICATION)
		};

		class VOYAGER_API AppTickEvent : public Event
		{
		public:
			AppTickEvent() {}

			EVENT_CLASS_TYPE(VE_APP_TICK)
				EVENT_CLASS_CATEGORY(VE_APPLICATION)
		};

		class VOYAGER_API AppUpdateEvent : public Event
		{
		public:
			AppUpdateEvent() {}

			EVENT_CLASS_TYPE(VE_APP_UPDATE)
				EVENT_CLASS_CATEGORY(VE_APPLICATION)
		};

		class VOYAGER_API AppRenderEvent : public Event
		{
		public:
			AppRenderEvent() {}

			EVENT_CLASS_TYPE(VE_APP_RENDER)
				EVENT_CLASS_CATEGORY(VE_APPLICATION)
		};
	}
}

#endif