#ifndef VE_KEYEVENT_H
#define VE_KEYEVENT_H

#include <sstream>

#include "Voyager/Event/Event.h"

namespace VE
{
	namespace Event
	{
		class VOYAGER_API KeyEvent : public Event
		{
		public:
			inline int getKeyCode() const { return _keycode; }

			EVENT_CLASS_CATEGORY(VE_KEYBOARD | VE_INPUT);
		protected:
			KeyEvent(int keycode) : _keycode(keycode) {}

			int _keycode;
		};

		class VOYAGER_API KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

			inline int getRepeatedCount() const { return _repeatCount; }

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << _keycode << " (" << _repeatCount << "repeats)";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_KEY_PRESSED);
		private:
			int _repeatCount;
		};

		class VOYAGER_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "KeyPressedEvent: " << _keycode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_KEY_RELEASED);
		};

		class VOYAGER_API KeyTypedEvent : public KeyEvent
		{
		public:
			KeyTypedEvent(int keycode) : KeyEvent(keycode) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "KeyTypedEvent: " << _keycode;
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_KEY_TYPED);
		};
	}
}

#endif