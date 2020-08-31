#ifndef VE_ENTRYPOINT_H
#define VE_ENTRYPOINT_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Log.h"
#include "Voyager/Core/Application.h"

#include <string>

#ifdef VE_PLATFORM_WINDOWS

extern VE::Core::Application* VE::Core::CreateApplication();
extern void VE::Core::printApplicationArgs();

int main(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if ((arg == "-h") || (arg == "--help")) {
			VE::Core::printApplicationArgs();
			return 0;
		}
	}

	VE::Core::Log::init();
	VE_CORE_WARN("Initalized log");
	auto app = VE::Core::CreateApplication();
	app->execute();
	delete app;
	return 0;
}

#endif

#endif
