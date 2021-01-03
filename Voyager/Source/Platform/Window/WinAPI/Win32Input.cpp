
#include "Platform/Window/WinAPI/Win32Input.h"

#include "Voyager/Core/Application.h"

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			bool Win32Input::isKeyPressedImpl(int keycode)
			{
				return true;
			}
			bool Win32Input::isMouseButtonPressedImpl(int button)
			{
				return true;
			}
			std::pair<float, float> Win32Input::getMousePositionImpl()
			{
				double xpos, ypos;
				ypos = xpos = 0.0;
				return { (float)xpos, (float)ypos };
			}
			float Win32Input::getMouseXImpl()
			{
				return 0.0f;
			}
			float Win32Input::getMouseYImpl()
			{
				return 0.0f;
			}
		}
	}
};