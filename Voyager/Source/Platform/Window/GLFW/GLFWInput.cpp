
#include "Platform/Window/GLFW/GLFWInput.h"

#include "Voyager/Core/Application.h"
#include <glfw3.h>

#include <WinUser.h>

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			bool GLFWInput::isKeyPressedImpl(int keycode)
			{
				auto window = static_cast<GLFWwindow*>(Core::Application::Get().getWindow().getNativeWindow());
				auto state = glfwGetKey(window, keycode);
				return state == GLFW_PRESS || state == GLFW_REPEAT;
			}
			bool GLFWInput::isMouseButtonPressedImpl(int button)
			{
				auto window = static_cast<GLFWwindow*>(Core::Application::Get().getWindow().getNativeWindow());
				auto state = glfwGetMouseButton(window, button);
				return state == GLFW_PRESS;
			}
			std::pair<float, float> GLFWInput::getMousePositionImpl()
			{
				auto window = static_cast<GLFWwindow*>(Core::Application::Get().getWindow().getNativeWindow());
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);

				return { (float)xpos, (float)ypos };
			}
			float GLFWInput::getMouseXImpl()
			{
				auto mousePos = getMousePositionImpl();
				return mousePos.first;
			}
			float GLFWInput::getMouseYImpl()
			{
				auto mousePos = getMousePositionImpl();
				return mousePos.second;
			}
		}
	}
};