#ifndef VE_WIN32_HANDLER_H
#define VE_WIN32_HANDLER_H

#include "Voyager/Core/IWindow.h"
#include "Voyager/Renderer/GraphicsContext.h"

#include "Platform/Window/WinAPI/Win32BaseWindow.h"

namespace VE
{
	namespace Platform 
	{
		namespace Window 
		{
			class Win32Handler : public Core::IWindow, public Win32BaseWindow<Win32Handler>
			{
			public:
				Win32Handler() {};
				virtual ~Win32Handler();

				virtual bool initialize(const Core::WindowProperties& props) override;

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

				inline virtual void* getNativeWindow() const { return hwnd; }

				LPCSTR className() const { return "Voyager_Win32_Window_Class"; }
				LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

			private:
				virtual void shutdown();

				unsigned int originalWidth = 0;
				unsigned int originalHeight = 0;

				Core::MonitorData monitorData = {};
				Core::WindowData windowData = {};

				Rendering::GraphicsContext* graphicsContext = nullptr;
			};
		}
	}
};

#endif