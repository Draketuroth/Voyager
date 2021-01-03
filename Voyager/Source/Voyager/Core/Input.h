#ifndef VE_INPUT_H
#define VE_INPUT_H

#include "Voyager/Core/Core.h"

namespace VE
{
	namespace Core 
	{
		class VOYAGER_API Input
		{
		public:
			inline static bool initialize();

			inline static bool isKeyPressed(int keycode) { return instance->isKeyPressedImpl(keycode); }
			inline static bool isMouseButtonPressed(int button) { return instance->isMouseButtonPressedImpl(button); }
			inline static std::pair<float, float> getMousePosition() { return instance->getMousePositionImpl(); }
			inline static float getMouseX() { return instance->getMouseXImpl(); }
			inline static float getMouseY() { return instance->getMouseYImpl(); }

		protected:
			virtual bool isKeyPressedImpl(int keycode) = 0;

			virtual bool isMouseButtonPressedImpl(int button) = 0;
			virtual std::pair<float, float> getMousePositionImpl() = 0;
			virtual float getMouseXImpl() = 0;
			virtual float getMouseYImpl() = 0;

		private:
			static VE::Core::Scope<Input> instance;
		};
	}
};

#endif