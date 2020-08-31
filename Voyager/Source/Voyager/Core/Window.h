#ifndef VE_WINDOW_H
#define VE_WINDOW_H

#include "Voyager/Core/Core.h"
#include "Voyager/Event/Event.h"

namespace VE
{
	namespace Core 
	{
		struct WindowProperties
		{
			std::string _title;
			unsigned int _width;
			unsigned int _height;
			bool _fullscreen;

			WindowProperties(const std::string& windowTitle = "VoyagerEngine", unsigned int windowWidth = 1280, unsigned int windowHeight = 760) :
				_title(windowTitle),
				_width(windowWidth),
				_height(windowHeight),
				_fullscreen(false)
			{
			}
		};

		class VOYAGER_API Window
		{
		public:
			using EventCallbackFn = std::function<void(Event::Event&)>;

			virtual ~Window() {}

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

			static Window* create(const WindowProperties& props = WindowProperties());
		};
	}
};

#endif