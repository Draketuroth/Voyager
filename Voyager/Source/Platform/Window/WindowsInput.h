#ifndef VE_WINDOWS_INPUT
#define VE_WINDOWS_INPUT

#include "Voyager/Core/Input.h"

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			class WindowsInput : public Core::Input
			{
			protected:
				virtual bool isKeyPressedImpl(int keycode) override;

				virtual bool isMouseButtonPressedImpl(int button) override;
				virtual std::pair<float, float> getMousePositionImpl() override;
				virtual float getMouseXImpl() override;
				virtual float getMouseYImpl() override;
			};
		}
	}
};

#endif