#ifndef VE_HARDWARE_INFO_H
#define VE_HARDWARE_INFO_H

#include <string>

namespace VE
{
    namespace Platform
    {
        namespace Renderer
        {
            struct GraphicsVendorInfo
            {
                GraphicsVendorInfo() : vendor("Unknown"), renderer("Unknown"), version("Unknown") {}
                std::string vendor;
                std::string renderer;
                std::string version;
            };
        }
    }
}

#endif