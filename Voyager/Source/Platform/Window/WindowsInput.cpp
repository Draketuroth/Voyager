
#include "WindowsInput.h"

#include "Voyager/Core/Application.h"
#include <glfw3.h>

namespace VE
{
	Core::Input* Core::Input::_instance = new Platform::Window::WindowsInput();

	namespace Platform 
	{
		namespace Window 
		{
			bool WindowsInput::isKeyPressedImpl(int keycode)
			{
				auto window = static_cast<GLFWwindow*>(Core::Application::Get().getWindow().getNativeWindow());
				auto state = glfwGetKey(window, keycode);
				return state == GLFW_PRESS || state == GLFW_REPEAT;
			}
			bool WindowsInput::isMouseButtonPressedImpl(int button)
			{
				auto window = static_cast<GLFWwindow*>(Core::Application::Get().getWindow().getNativeWindow());
				auto state = glfwGetMouseButton(window, button);
				return state == GLFW_PRESS;
			}
			std::pair<float, float> WindowsInput::getMousePositionImpl()
			{
				auto window = static_cast<GLFWwindow*>(Core::Application::Get().getWindow().getNativeWindow());
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);

				return { (float)xpos, (float)ypos };
			}
			float WindowsInput::getMouseXImpl()
			{
				auto mousePos = getMousePositionImpl();
				return mousePos.first;
			}
			float WindowsInput::getMouseYImpl()
			{
				auto mousePos = getMousePositionImpl();
				return mousePos.second;
			}
		}
	}
};