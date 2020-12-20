#ifndef VE_WIN32WINDOW_H
#define VE_WIN32WINDOW_H

#include "Voyager/Core/IWindow.h"
#include "Voyager/Renderer/GraphicsContext.h"

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			class Win32Handler : public Core::IWindow
			{
			public:
				Win32Handler(const Core::WindowProperties& props);
				virtual ~Win32Handler();

				void onUpdate() override;

				inline unsigned int getWidth() const override { return windowData.width; }
				inline unsigned int getHeight() const override { return windowData.height; }
				inline unsigned int getMonitorWidth() const override { return monitorData.width; }
				inline unsigned int getMonitorHeight() const override { return monitorData.height; }

				inline void setEventCallback(const Core::EventCallbackFn& callback) override { windowData.eventCallback = callback; }
				void toggleFullscreen() override;
				void toggleCaptureMouse() override;
				void setCaptureMouse(bool enabled) override;
				void setVSync(bool enabled) override;
				bool isVSync() const override;
				bool isMouseCaptured() const override;
				bool isFullscreen() const override;

				inline virtual void* getNativeWindow() const { return nullptr; }

			private:
				virtual void init(const Core::WindowProperties& props);
				virtual void shutdown();

				unsigned int originalWidth;
				unsigned int originalHeight;

				Core::MonitorData monitorData;
				Core::WindowData windowData;
				Rendering::GraphicsContext* graphicsContext;
			};
		}
	}
};

#endif