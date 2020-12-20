#include "Win32Handler.h"

#include "Voyager/Event/ApplicationEvent.h"
#include "Voyager/Event/KeyEvent.h"
#include "Voyager/Event/MouseEvent.h"

#include "Voyager/Core/Log.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Voyager/Renderer/RenderCommand.h"

#include <stb_image.h>

namespace VE
{
	namespace Platform
	{
		namespace Window
		{
			Win32Handler::Win32Handler(const Core::WindowProperties& props)
			{
				init(props);
			}

			Win32Handler::~Win32Handler()
			{
				shutdown();
			}

			void Win32Handler::onUpdate()
			{
				graphicsContext->swapBuffers();
			}

			void Win32Handler::toggleFullscreen()
			{
				if (!windowData.fullScreen)
				{
					// Store previous window position for repositioning when exiting fullscreen mode.
					windowData.fullScreen = !windowData.fullScreen;
				}
				else
				{
					windowData.width = originalWidth;
					windowData.height = originalHeight;
					windowData.fullScreen = !windowData.fullScreen;
				}
			}

			void Win32Handler::toggleCaptureMouse()
			{
				if (!windowData.mouseCaptured)
				{
					// glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					windowData.mouseCaptured = !windowData.mouseCaptured;
				}
				else
				{
					// glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					windowData.mouseCaptured = false;
				}
			}

			void Win32Handler::setCaptureMouse(bool enabled)
			{
				if (enabled)
				{

				}
				else
				{

				}
				windowData.mouseCaptured = enabled;
			}

			void Win32Handler::setVSync(bool enabled)
			{
				if (enabled)
				{

				}
				else
				{

				}
				windowData.vsync = enabled;
			}

			bool Win32Handler::isVSync() const
			{
				return windowData.vsync;
			}

			bool Win32Handler::isMouseCaptured() const
			{
				return windowData.mouseCaptured;
			}

			bool Win32Handler::isFullscreen() const
			{
				return windowData.fullScreen;
			}

			void Win32Handler::init(const Core::WindowProperties& props)
			{
				windowData.title = props.title;
				originalWidth = windowData.width = props.width;
				originalHeight = windowData.height = props.height;
				windowData.fullScreen = props.fullscreen;

				VE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);
			}

			void Win32Handler::shutdown()
			{
				
			}
		}
	}
};
                                                                                                          