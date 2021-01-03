
#include "Voyager/Core/Input.h"
#include "Platform/Window/GLFW/GLFWInput.h"
#include "Platform/Window/WinAPI/Win32Input.h"

#include "Platform/Window/WindowAPIHandler.h"
#include "Log.h"

VE::Core::Scope<VE::Core::Input> VE::Core::Input::instance(nullptr);

namespace VE
{
	namespace Core
	{
		inline bool Input::initialize()
		{
			switch (Platform::Window::WindowAPIHandler::getAPI())
			{
			case Platform::API::WindowAPI::None:
				VE_CORE_ASSERT(false, "WindowAPI::None is not supported");
				return false;
			case Platform::API::WindowAPI::GLFW: 
				instance.reset(new VE::Platform::Window::GLFWInput);
				return true;
			case Platform::API::WindowAPI::Win32: 
				instance.reset(new VE::Platform::Window::Win32Input);
				return true;
			}
		}
	}
}