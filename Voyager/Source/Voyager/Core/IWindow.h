#ifndef VE_WINDOW_H
#define VE_WINDOW_H

#include "Voyager/Core/Core.h"
#include "Voyager/Event/Event.h"

namespace VE
{
	namespace Core 
	{
		using EventCallbackFn = std::function<void(Event::Event&)>;

		struct WindowProperties
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			bool fullscreen;

			WindowProperties(const std::string& windowTitle = "VoyagerEngine", unsigned int windowWidth = 1280, unsigned int windowHeight = 760) :
				title(windowTitle),
				width(windowWidth),
				height(windowHeight),
				fullscreen(false)
			{
			}

			WindowProperties(const WindowProperties& other)
			{
				title = other.title;
				width = other.width;
				height = other.height;
				fullscreen = other.fullscreen;
			}
		};

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

		class VOYAGER_API IWindow
		{
		public:
			virtual ~IWindow() = default;

			virtual void onUpdate() = 0;

			virtual unsigned int getWidth() const = 0;
			virtual unsigned int getHeight() const = 0;
			virtual unsigned int getMonitorWidth() const = 0;
			virtual unsigned int getMonitorHeight() const = 0;

			virtual void setEventCallback(const EventCallbackFn& callback) = 0;
			virtual void toggleFullscreen() = 0;
			virtual void toggleCaptureMouse() = 0;
			virtual void setCaptureMouse(bool enabled) = 0;
			virtual void setVSync(bool enabled) = 0;
			virtual bool isVSync() const = 0;
			virtual bool isMouseCaptured() const = 0;
			virtual bool isFullscreen() const = 0;

			virtual void* getNativeWindow() const = 0;

			static IWindow* create(const WindowProperties& props = WindowProperties());
		};
	}
};

#endif