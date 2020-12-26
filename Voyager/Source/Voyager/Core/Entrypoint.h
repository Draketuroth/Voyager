#ifndef VE_ENTRYPOINT_H
#define VE_ENTRYPOINT_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Log.h"
#include "Voyager/Core/Application.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/Window/WindowAPIHandler.h"

#include <string>

#ifdef VE_PLATFORM_WINDOWS

extern VE::Core::Application* VE::Core::CreateApplication();
extern void VE::Core::printApplicationArgs();

int main(int argc, char** argv)
{
	VE::Platform::API::RenderAPI renderAPI = VE::Platform::API::RenderAPI::None;

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) {
			VE::Core::printApplicationArgs();
			return 0;
		}
		else if (arg == "--renderapi") 
		{
			std::string renderApiSelection = argv[i + 1];
			if (renderApiSelection == "OpenGL") 
			{
				renderAPI = VE::Platform::API::RenderAPI::OpenGL;
			}
			else if (renderApiSelection == "DirectX12") 
			{
				renderAPI = VE::Platform::API::RenderAPI::DirectX12;
			}
		}
	}

	VE::Platform::Window::WindowAPIHandler::setAPI(VE::Platform::API::WindowAPI::Win32); // TODO: Temporary forcing for development.
	VE::Platform::Renderer::RendererAPIHandler::setAPI(VE::Platform::API::RenderAPI::DirectX12);  // TODO: Temporary forcing for development.

	VE::Core::Log::init();
	VE_CORE_WARN("Initalized log");
	auto app = VE::Core::CreateApplication();

	app->execute();

	delete app;
	return 0;
}

#endif

#endif
