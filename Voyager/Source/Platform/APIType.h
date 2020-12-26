#ifndef VE_PLATFORM_API_TYPE_H
#define VE_PLATFORM_API_TYPE_H

namespace VE 
{
    namespace Platform 
    {
        namespace API 
        {
            enum class WindowAPI
            {
                None = 0,
                GLFW = 1,
                Win32 = 2
            };

            enum class RenderAPI
            {
                None = 0,
                OpenGL = 1,
                DirectX12 = 2,
                Vulcan = 3
            };
        }
    }
}

#endif