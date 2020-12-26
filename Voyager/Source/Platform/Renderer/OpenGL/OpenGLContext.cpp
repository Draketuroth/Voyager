
#include "OpenGLContext.h"
#include "Voyager/Core/Log.h"

#include <glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : _windowHandle(windowHandle)
			{
				VE_ASSERT(windowHandle, "Window handle is null!");
			}
			void OpenGLContext::init()
			{
				glfwMakeContextCurrent(_windowHandle);
				int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
				VE_CORE_ASSERT(status, "Failed to initialize Glad!");

				VE_CORE_INFO("OpenGL Info:");
				VE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
				VE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
				VE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
			}
			void OpenGLContext::swapBuffers()
			{
				glfwSwapBuffers(_windowHandle);
			}
		}
	}
}