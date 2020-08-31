#ifndef VE_APPLICATION_H
#define VE_APPLICATION_H

#include "Voyager/Core/Core.h"

#include "Voyager/Core/Window.h"
#include "Voyager/Core/LayerStack.h"
#include "Voyager/Core/Timestep.h"

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

			inline Window& getWindow() { return *_window; }

			inline static Application& Get() { return *_instance; }

		private:
			bool onWindowClose(Event::WindowCloseEvent& e);
			bool onWindowResize(Event::WindowResizeEvent& e);
			bool onMouseCaptured(Event::KeyPressedEvent& e);

			VE::Core::Scope<Window> _window;
			ImGuiLayer* _imGuiLayer;
			static Application* _instance;

			bool _running = true;
			bool _minimized = false;
			LayerStack _layerStack;

			float _lastFrameTime = 0.0f;
		};

		// To be defined in client.
		Application* CreateApplication();
		void printApplicationArgs();
	}
};

#endif