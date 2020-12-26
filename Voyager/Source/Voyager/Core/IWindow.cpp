
#include "Voyager/Core/IWindow.h"
#include "Platform/Window/GLFW/GLFWHandler.h"
#include "Platform/Window/WinAPI/Win32Handler.h"

#include "Platform/Window/WindowAPIHandler.h"
#include "Log.h"

namespace VE 
{
    namespace Core 
    {
		Core::IWindow* Core::IWindow::create()
		{
			switch (Platform::Window::WindowAPIHandler::getAPI())
			{
				case Platform::API::WindowAPI::None:
					VE_CORE_ASSERT(false, "WindowAPI::None is not supported");
					return nullptr;
				case Platform::API::WindowAPI::GLFW: return new Platform::Window::GLFWHandler();
				case Platform::API::WindowAPI::Win32: return new Platform::Window::Win32Handler();
			}
		}
    }
}