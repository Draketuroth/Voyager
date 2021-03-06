
#include "Win32Window.h"

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

	Core::Window* Core::Window::create(const Core::WindowProperties& props)
	{
		return new Platform::Window::Win32Window(props);
	}

	namespace Platform
	{
		namespace Window
		{
			Win32Window::Win32Window(const Core::WindowProperties& props)
			{
				init(props);
			}

			Win32Window::~Win32Window()
			{
				shutdown();
			}

			void Win32Window::onUpdate()
			{
				glfwPollEvents();
				_context->swapBuffers();
			}

			void Win32Window::toggleFullscreen()
			{
				GLFWmonitor* monitor = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(monitor);

				if (!_windowData.fullScreen)
				{
					// Store previous window position for repositioning when exiting fullscreen mode.
					glfwGetWindowPos(_window, &_windowData.x, &_windowData.y);

					glfwSetWindowMonitor(_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
					_windowData.fullScreen = !_windowData.fullScreen;
				}
				else
				{
					_windowData.width = _originalWidth;
					_windowData.height = _originalHeight;
					glfwSetWindowMonitor(_window, nullptr, _windowData.x, _windowData.y, _windowData.width, _windowData.height, mode->refreshRate);
					_windowData.fullScreen = !_windowData.fullScreen;
				}
			}

			void Win32Window::toggleCaptureMouse()
			{
				if (!_windowData.mouseCaptured)
				{
					glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					_windowData.mouseCaptured = !_windowData.mouseCaptured;
				}
				else
				{
					glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					_windowData.mouseCaptured = false;
				}
			}

			void Win32Window::setCaptureMouse(bool enabled)
			{
				if (enabled)
				{
					glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				}
				else
				{
					glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				}
				_windowData.mouseCaptured = enabled;
			}

			void Win32Window::setVSync(bool enabled)
			{
				if (enabled)
				{
					glfwSwapInterval(1);
				}
				else
				{
					glfwSwapInterval(0);
				}
				_windowData.vsync = enabled;
			}

			bool Win32Window::isVSync() const
			{
				return _windowData.vsync;
			}

			bool Win32Window::isMouseCaptured() const
			{
				return _windowData.mouseCaptured;
			}

			bool Win32Window::isFullscreen() const
			{
				return _windowData.fullScreen;
			}

			void Win32Window::init(const Core::WindowProperties& props)
			{
				_windowData.title = props._title;
				_originalWidth = _windowData.width = props._width;
				_originalHeight = _windowData.height = props._height;
				_windowData.fullScreen = props._fullscreen;

				VE_CORE_INFO("Creating window {0} ({1}, {2})", props._title, props._width, props._height);

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

				_monitorData.width = mode->width;
				_monitorData.height = mode->height;

				// If window is configured to be started in fullscreen mode, override 
				_window = props._fullscreen ? glfwCreateWindow((int)mode->width, mode->height, props._title.c_str(), monitor, nullptr) :
					glfwCreateWindow((int)props._width, (int)props._height, props._title.c_str(), nullptr, nullptr);

				_context = new OpenGL::OpenGLContext(_window);
				_context->init();

				glfwSetWindowUserPointer(_window, &_windowData);

				if (props._fullscreen)
				{
					VE::Rendering::RenderCommand::setViewport(0, 0, mode->width, mode->height);
				}
				else
				{
					VE::Rendering::RenderCommand::setViewport(0, 0, props._width, props._height);
				}

				setVSync(true);
				setCaptureMouse(true);

				// Load window icon
				GLFWimage icons[1];
				int channels;
				icons[0].pixels = stbi_load("Textures\\logo.png", &icons[0].width, &icons[0].height, &channels, 0);
				if (icons[0].pixels != nullptr)
				{
					glfwSetWindowIcon(_window, 1, icons);
				}

				// Set GLFW callbacks.
				glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, int width, int height)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						data.width = width;
						data.height = height;

						Event::WindowResizeEvent event(width, height);
						VE_CORE_WARN("{0}, {1}", width, height);
						data.eventCallback(event);

					});

				glfwSetWindowCloseCallback(_window, [](GLFWwindow* window)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						Event::WindowCloseEvent event;
						data.eventCallback(event);
					});

				// TODO: Convert to general engine keycode.
				glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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

				glfwSetCharCallback(_window, [](GLFWwindow* window, unsigned int keycode)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

						Event::KeyTypedEvent event(keycode);
						data.eventCallback(event);
					});

				glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

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

				glfwSetScrollCallback(_window, [](GLFWwindow* window, double xoffset, double yoffset)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

						Event::MouseScrolledEvent event((float)xoffset, (float)yoffset);
						data.eventCallback(event);
					});

				glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos)
					{
						WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
						Event::MouseMovedEvent event((float)xpos, (float)ypos);
						data.eventCallback(event);
					});
			}

			void Win32Window::shutdown()
			{
				glfwDestroyWindow(_window);
			}
		}
	}
};
                                                                                                          