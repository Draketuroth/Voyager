#include "GLFWHandler.h"

#include "Voyager/Event/ApplicationEvent.h"
#include "Voyager/Event/KeyEvent.h"
#include "Voyager/Event/MouseEvent.h"

#include "Voyager/Core/Log.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Voyager/Renderer/RenderCommand.h"

#include <stb_image.h>

namespace VE
{
	static bool glfwInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		VE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	namespace Platform
	{
		namespace Window
		{
			GLFWHandler::GLFWHandler(const Core::WindowProperties& props)
			{
				init(props);
			}

			GLFWHandler::~GLFWHandler()
			{
				shutdown();
			}

			void GLFWHandler::onUpdate()
			{
				glfwPollEvents();
				graphicsContext->swapBuffers();
			}

			void GLFWHandler::toggleFullscreen()
			{
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				if (!windowData.fullScreen)
				{
					// Store previous window position for repositioning when exiting fullscreen mode.
					glfwGetWindowPos(window, &windowData.x, &windowData.y);

					glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
					windowData.fullScreen = !windowData.fullScreen;
				}
				else
				{
					windowData.width = originalWidth;
					windowData.height = originalHeight;
					glfwSetWindowMonitor(window, nullptr, windowData.x, windowData.y, windowData.width, windowData.height, mode->refreshRate);
					windowData.fullScreen = !windowData.fullScreen;
				}
			}

			void GLFWHandler::toggleCaptureMouse()
			{
				if (!windowData.mouseCaptured)
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					windowData.mouseCaptured = !windowData.mouseCaptured;
				}
				else
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					windowData.mouseCaptured = false;
				}
			}

			void GLFWHandler::setCaptureMouse(bool enabled)
			{
				if (enabled)
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				}
				else
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				windowData.mouseCaptured = enabled;
			}

			void GLFWHandler::setVSync(bool enabled)
			{
				if (enabled)
				{
					glfwSwapInterval(1);
				}
				else
				{
					glfwSwapInterval(0);
				}
				windowData.vsync = enabled;
			}

			bool GLFWHandler::isVSync() const
			{
				return windowData.vsync;
			}

			bool GLFWHandler::isMouseCaptured() const
			{
				return windowData.mouseCaptured;
			}

			bool GLFWHandler::isFullscreen() const
			{
				return windowData.fullScreen;
			}

			void GLFWHandler::init(const Core::WindowProperties& props)
			{
				windowData.title = props.title;
				originalWidth = windowData.width = props.width;
				originalHeight = windowData.height = props.height;
				windowData.fullScreen = props.fullscreen;

				VE_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

				if (!glfwInitialized)
				{
					int success = glfwInit();
					if (!success)
					{
						exit(-1);
					}
					glfwSetErrorCallback(GLFWErrorCallback);

					glfwInitialized = true;
				}

				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				monitorData.width = mode->width;
				monitorData.height = mode->height;

				// If window is configured to be started in fullscreen mode, override 
				window = props.fullscreen ? glfwCreateWindow((int)mode->width, mode->height, props.title.c_str(), monitor, nullptr) :
					glfwCreateWindow((int)props.width, (int)props.height, props.title.c_str(), nullptr, nullptr);

				graphicsContext = new OpenGL::OpenGLContext(window);
				graphicsContext->init();

				glfwSetWindowUserPointer(window, &windowData);

				if (props.fullscreen)
				{
					VE::Rendering::RenderCommand::setViewport(0, 0, mode->width, mode->height);
				}
				else
				{
					VE::Rendering::RenderCommand::setViewport(0, 0, props.width, props.height);
				}

				setVSync(true);
				setCaptureMouse(true);

				// Load window icon
				GLFWimage icons[1];
				int channels;
				icons[0].pixels = stbi_load("Textures\\logo.png", &icons[0].width, &icons[0].height, &channels, 0);
				if (icons[0].pixels != nullptr)
				{
					glfwSetWindowIcon(window, 1, icons);
				}

				// Set GLFW callbacks.
				glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);
						data.width = width;
						data.height = height;

						Event::WindowResizeEvent event(width, height);
						VE_CORE_WARN("{0}, {1}", width, height);
						data.eventCallback(event);

					});

				glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);
						Event::WindowCloseEvent event;
						data.eventCallback(event);
					});

				// TODO: Convert to general engine keycode.
				glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);

						switch (action)
						{
						case GLFW_PRESS:
						{
							Event::KeyPressedEvent event(key, 0);
							data.eventCallback(event);
							break;
						}
						case GLFW_RELEASE:
						{
							Event::KeyReleasedEvent event(key);
							data.eventCallback(event);
							break;
						}
						case GLFW_REPEAT:
						{
							Event::KeyPressedEvent event(key, 1);
							data.eventCallback(event);
							break;
						}
						}
					});

				glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int keycode)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);

						Event::KeyTypedEvent event(keycode);
						data.eventCallback(event);
					});

				glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);

						switch (action)
						{
						case GLFW_PRESS:
						{
							Event::MouseButtonPressedEvent event(button);
							data.eventCallback(event);
							break;
						}
						case GLFW_RELEASE:
						{
							Event::MouseButtonReleasedEvent event(button);
							data.eventCallback(event);
							break;
						}
						}

					});

				glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);

						Event::MouseScrolledEvent event((float)xoffset, (float)yoffset);
						data.eventCallback(event);
					});

				glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos)
					{
						Core::WindowData& data = *(Core::WindowData*)glfwGetWindowUserPointer(window);
						Event::MouseMovedEvent event((float)xpos, (float)ypos);
						data.eventCallback(event);
					});
			}

			void GLFWHandler::shutdown()
			{
				glfwDestroyWindow(window);
			}
		}
	}
};
                                                                                                          