
#include "Voyager/Core/IWindow.h"
#include "Platform/Window/GLFW/GLFWHandler.h"
#include "Platform/Window/WIN/Win32Handler.h"

#include "Platform/Window/WindowAPIHandler.h"
#include "Log.h"

namespace VE 
{
    namespace Core 
    {
		Core::IWindow* Core::IWindow::create(const Core::WindowProperties& props)
		{
			switch (Platform::Window::WindowAPIHandler::getAPI())
			{
				case Platform::API::WindowAPI::GLFW: return new Platform::Window::GLFWHandler(props);
				case Platform::API::WindowAPI::WIN: return new Platform::Window::Win32Handler(props);
			}

			VE_CORE_ASSERT(false, "Unknown WindowAPI!");
			return nullptr;
		}
    }
}