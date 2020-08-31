#ifndef VE_WIN32WINDOW_H
#define VE_WIN32WINDOW_H

#include <glfw3.h>

#include "Voyager/Core/Window.h"
#include "Voyager/Renderer/GraphicsContext.h"

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			class Win32Window : public Core::Window
			{
			public:
				Win32Window(const Core::WindowProperties& props);
				virtual ~Win32Window();

				void onUpdate() override;

				inline unsigned int getWidth() const override { return _windowData.width; }
				inline unsigned int getHeight() const override { return _windowData.height; }
				inline unsigned int getMonitorWidth() const override { return _monitorData.width; }
				inline unsigned int getMonitorHeight() const override { return _monitorData.height; }

				inline void setEventCallback(const EventCallbackFn& callback) override { _windowData.eventCallback = callback; }
				void toggleFullscreen() override;
				void toggleCaptureMouse() override;
				void setCaptureMouse(bool enabled) override;
				void setVSync(bool enabled) override;
				bool isVSync() const override;
				bool isMouseCaptured() const override;
				bool isFullscreen() const override;

				inline virtual void* getNativeWindow() const { return _window; }

			private:
				virtual void init(const Core::WindowProperties& props);
				virtual void shutdown();

				struct WindowData
				{
					std::string title;
					unsigned int width;
					unsigned int height;
					int x;
					int y;
					bool vsync;
					bool mouseCaptured;
					bool fullScreen;

					EventCallbackFn eventCallback;
				};

				struct MonitorData
				{
					unsigned int width;
					unsigned int height;
				};

				unsigned int _originalWidth;
				unsigned int _originalHeight;

				MonitorData _monitorData;
				WindowData _windowData;
				GLFWwindow* _window;
				Rendering::GraphicsContext* _context;
			};
		}
	}
};

#endif