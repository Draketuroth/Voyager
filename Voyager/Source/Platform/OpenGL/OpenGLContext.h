#ifndef VE_OPENGL_CONTEXT_H
#define VE_OPENGL_CONTEXT_H

#include "Voyager/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLContext : public Rendering::GraphicsContext
			{
			public:
				OpenGLContext(GLFWwindow* windowHandle);

				virtual void init() override;
				virtual void swapBuffers() override;

			private:
				GLFWwindow* _windowHandle;
			};
		}
	}
}

#endif