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
                GLFW = 0,
                WIN = 1
            };

            enum class RenderAPI
            {
                None = 0,
                OpenGL = 1,
                DirectX = 2,
                Vulcan = 3
            };
        }
    }
}

#endif