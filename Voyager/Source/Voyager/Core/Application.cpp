#include "Application.h"

#include "Voyager/Core/Log.h"

#include "Voyager/Core/Input.h"

#include "Voyager/Renderer/Renderer.h"

#include "Voyager/Core/KeyCodes.h"

#include "Voyager/IO/JSONParser.h"

#include <fstream>

#include <glfw3.h>

namespace VE
{
	namespace Core 
	{
	# define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

		Application* Application::_instance = nullptr;

		Application::Application()
		{
			VE_ASSERT(!_instance, "Application already exist!");
			_instance = this;

			WindowProperties windowProps;

			std::string viewConfigPath = "Config\\Views.json";
			std::string buffer = VE::IO::readFileToString(viewConfigPath);

			std::string errorCode;
			auto viewConfig = VE::IO::JSON::JSONNode::parse(buffer, errorCode, VE::IO::JSON::JSONParseStrategy::COMMENTS);
			if (!viewConfig.isNull())
			{
				auto displayNode = viewConfig["display"].asObject();
				windowProps._title = displayNode["title"].asString();
				windowProps._fullscreen = displayNode["fullscreen"].asBoolean();
				windowProps._width = displayNode["width"].asNumber();
				windowProps._height = displayNode["height"].asNumber();
			}
			else
			{
				VE_CORE_WARN("Failed reading Views.json, defaulting to standard config. Error: " + errorCode);
			}

			_window = VE::Core::Scope<Window>(Window::create(windowProps));
			_window->setEventCallback(BIND_EVENT_FN(onEvent));

			_imGuiLayer = new ImGuiLayer();
			pushOverlay(_imGuiLayer);
		}

		Application::~Application()
		{

		}

		void Application::execute()
		{
			while (_running)
			{
				float time = (float)glfwGetTime();
				Timestep timestep = time - _lastFrameTime;
				_lastFrameTime = time;

				if (!_minimized)
				{
					for (Layer* layer : _layerStack)
					{
						layer->onUpdate(timestep);
					}
				}

				_imGuiLayer->begin();
				for (Layer* layer : _layerStack)
				{
					layer->onImGuiRender();
				}
				_imGuiLayer->end();


				_window->onUpdate();
			}
		}

		void Application::onEvent(Event::Event& e)
		{
			Event::EventHandler handler(e);
			handler.execute<Event::WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
			handler.execute<Event::WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));
			handler.execute<Event::KeyPressedEvent>(BIND_EVENT_FN(onMouseCaptured));

			for (auto it = _layerStack.end(); it != _layerStack.begin(); )
			{
				(*--it)->onEvent(e);
				if (e.handled)
				{
					break;
				}
			}
		}

		void Application::pushLayer(Layer* layer)
		{
			_layerStack.pushLayer(layer);
		}

		void Application::pushOverlay(Layer* layer)
		{
			_layerStack.pushOverlay(layer);
		}

		bool Application::onWindowClose(Event::WindowCloseEvent& e)
		{
			_running = false;
			return true;
		}

		bool Application::onWindowResize(Event::WindowResizeEvent& e)
		{
			if (e.getWidth() == 0 || e.getHeight() == 0)
			{
				_minimized = true;
				return false;
			}
			_minimized = false;
			Rendering::Renderer::onWindowResize(e.getWidth(), e.getHeight());

			return false;
		}

		bool Application::onMouseCaptured(Event::KeyPressedEvent& e)
		{
			if (e.getKeyCode() == VE_KEY_TAB)
			{
				_window->toggleCaptureMouse();
			}
			if (e.getKeyCode() == VE_KEY_F)
			{
				_window->toggleFullscreen();
				if (_window->isFullscreen())
				{
					Rendering::Renderer::onWindowResize(_window->getMonitorWidth(), _window->getMonitorHeight());
				}
				else
				{
					Rendering::Renderer::onWindowResize(_window->getWidth(), _window->getHeight());
				}
			}
			if (e.getKeyCode() == VE_KEY_ESCAPE)
			{
				_running = false;
				return true;
			}

			return false;
		}
	}
}
