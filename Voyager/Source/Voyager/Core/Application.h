#ifndef VE_APPLICATION_H
#define VE_APPLICATION_H

#include "Voyager/Core/Core.h"

#include "Voyager/Core/IWindow.h"
#include "Voyager/Core/LayerStack.h"
#include "Voyager/Core/Timestep.h"
#include "Voyager/Core/Timer.h"

#include "Voyager/Event/Event.h"
#include "Voyager/Event/ApplicationEvent.h"
#include "Voyager/Event/KeyEvent.h"
#include "Voyager/Event/FileEvent.h"
#include "Voyager/Event/EntityEvent.h"
#include "Voyager/Event/ComponentEvent.h"

#include "Platform/OpenGL/OpenGLShaderset.h"

#include "Voyager/ImGui/ImGuiLayer.h"

#include "Voyager/Renderer/Camera.h"

#include <memory>

namespace VE
{
	namespace Core 
	{
		class VOYAGER_API Application
		{
		public:
			Application();
			virtual ~Application();

			void execute();

			void onEvent(Event::Event& e);

			void pushLayer(Layer* layer);
			void pushOverlay(Layer* layer);

			void popLayer(Layer* layer);
			void popOverlay(Layer* layer);

			inline IWindow& getWindow() { return *windowInterface; }

			inline static Application& Get() { return *instance; }

		private:
			bool onWindowClose(Event::WindowCloseEvent& e);
			bool onWindowResize(Event::WindowResizeEvent& e);
			bool onMouseCaptured(Event::KeyPressedEvent& e);

		protected:
			VE::Core::Scope<IWindow> windowInterface;

		private:
			ImGuiLayer* imguiLayer;
			static Application* instance;

			bool running = true;
			bool minimized = false;
			LayerStack layer_stack;
			Timer timer;

			double lastFrameTimeMs = 0.0;
		};

		// To be defined in client.
		Application* CreateApplication();
		void printApplicationArgs();
	}
};

#endif