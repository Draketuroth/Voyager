#ifndef VE_MOUSEEVENT_H
#define VE_MOUSEEVENT_H

#include <sstream>

#include "Voyager/Event/Event.h"

namespace VE
{
	namespace Event
	{
		class VOYAGER_API MouseMovedEvent : public Event
		{
		public:
			MouseMovedEvent(float xcoord, float ycoord) : _xcoord(xcoord), _ycoord(ycoord) {}

			inline float getXCoord() const { return _xcoord; }
			inline float getYCoord() const { return _ycoord; }

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "MouseEvent: " << _xcoord << ", " << _ycoord;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_MOUSE_MOVED)
				EVENT_CLASS_CATEGORY(VE_MOUSE | VE_INPUT)

		private:
			float _xcoord;
			float _ycoord;
		};

		class VOYAGER_API MouseScrolledEvent : public Event
		{
		public:
			MouseScrolledEvent(float xoffset, float yoffset) : _xoffset(xoffset), _yoffset(yoffset) {}

			inline float getXOffset() const { return _xoffset; }
			inline float getYOffset() const { return _yoffset; }

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "MouseScrolledEvent: " << _xoffset << ", " << _yoffset;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_MOUSE_SCROLLED)
				EVENT_CLASS_CATEGORY(VE_MOUSE | VE_INPUT)
		private:
			float _xoffset;
			float _yoffset;
		};

		class VOYAGER_API MouseButtonEvent : public Event
		{
		public:
			inline int getMouseButton() const { return _button; }

			EVENT_CLASS_CATEGORY(VE_MOUSE | VE_INPUT)

		protected:
			MouseButtonEvent(int button) : _button(button) {}
			int _button;
		};

		class VOYAGER_API MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "MouseButtonPressedEvent: " << _button;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_MOUSE_PRESSED)
		};

		class VOYAGER_API MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "MouseButtonReleasedEvent: " << _button;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_MOUSE_RELEASED)
		};
	}
}

#endif