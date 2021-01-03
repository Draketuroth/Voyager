#include "Platform/Window/WinAPI/Win32Handler.h"

#include "Voyager/Event/ApplicationEvent.h"
#include "Voyager/Event/KeyEvent.h"
#include "Voyager/Event/MouseEvent.h"

#include "Voyager/Core/Log.h"
#include "Voyager/Core/Input.h"

#include "Voyager/IO/Parsing.h"

#include "Platform/Renderer/DirectX12/DirectX12Context.h"
#include "Voyager/Renderer/RenderCommand.h"

namespace VE
{
	namespace Platform
	{
		namespace Window
		{
			bool Win32Handler::initialize(const Core::WindowProperties& props)
			{
				windowData.title = props.title;
				originalWidth = windowData.width = props.width;
				originalHeight = windowData.height = props.height;
				windowData.fullScreen = props.fullscreen;

				monitorData.width = GetSystemMetrics(SM_CXFULLSCREEN);
				monitorData.height = GetSystemMetrics(SM_CYFULLSCREEN);

				bool status = createWin32Window(windowData.title.c_str(),
					WS_OVERLAPPEDWINDOW,
					0,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					windowData.width,
					windowData.height,
					this
					);
				if (!status)
				{
					return false;
				}

				ShowWindow(hwnd, SW_SHOWNORMAL);
				SetCapture(hwnd);

				graphicsContext = new Renderer::DirectX::DirectX12Context();
				if (!graphicsContext->init()) 
				{
					return false;
				}

				return true;
			}

			Win32Handler::~Win32Handler()
			{
				shutdown();
			}

			void Win32Handler::onUpdate()
			{
				MSG msg = {};
				GetMessage(&msg, NULL, 0, 0);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				// graphicsContext->swapBuffers();
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

			LRESULT Win32Handler::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
			{
				switch (uMsg)
				{
				case WM_DESTROY:
				{
					PostQuitMessage(0);
					return 0;
				}

				case WM_CLOSE: 
				{
					Win32Handler& data = *(Win32Handler*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
					if (data.windowData.eventCallback)
					{
						Event::WindowCloseEvent event;
						data.windowData.eventCallback(event);
					}
					return 0;
				}

				case WM_SIZE:
				{
					Win32Handler& data = *(Win32Handler*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
					if (data.windowData.eventCallback) 
					{
						int width = LOWORD(lParam);  // Macro to get the low-order word.
						int height = HIWORD(lParam); // Macro to get the high-order word.

						data.windowData.width = width;
						data.windowData.height = height;

						Event::WindowResizeEvent event(width, height);
						VE_CORE_WARN("{0}, {1}", width, height);
						data.windowData.eventCallback(event);
					}
					return 0;
				}
				break;

				case WM_PAINT:
				{
					PAINTSTRUCT ps;
					HDC hdc = BeginPaint(hwnd, &ps);
					FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
					EndPaint(hwnd, &ps);
					return 0;
				}

				default:
					return DefWindowProc(hwnd, uMsg, wParam, lParam);
				}
				return TRUE;
			}

			void Win32Handler::shutdown()
			{
				DestroyWindow(hwnd);
			}
		}
	}
};
                
