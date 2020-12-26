#include "Application.h"

#include "Voyager/Core/Log.h"

#include "Voyager/Core/Input.h"

#include "Voyager/Renderer/Renderer.h"

#include "Voyager/Core/KeyCodes.h"

#include "Voyager/IO/JSONParser.h"
#include "Voyager/IO/Parsing.h"

#include <fstream>

#include <glfw3.h>

namespace VE
{
	namespace Core 
	{
	# define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

		Application* Application::instance = nullptr;

		Application::Application()
		{
			VE_ASSERT(!instance, "Application already exist!");
			instance = this;

			timer.initTimer();

			WindowProperties windowProps;

			std::string viewConfigPath = "Config\\Views.json";
			std::string buffer = VE::IO::readFileToString(viewConfigPath);

			std::string errorCode;
			auto viewConfig = VE::IO::JSON::JSONNode::parse(buffer, errorCode, VE::IO::JSON::JSONParseStrategy::COMMENTS);
			if (!viewConfig.isNull())
			{
				auto displayNode = viewConfig["display"].asObject();
				windowProps.title = displayNode["title"].asString();
				windowProps.fullscreen = displayNode["fullscreen"].asBoolean();
				windowProps.width = displayNode["width"].asNumber();
				windowProps.height = displayNode["height"].asNumber();
			}
			else
			{
				VE_CORE_WARN("Failed reading Views.json, defaulting to standard config. Error: " + errorCode);
			}

			VE_CORE_INFO("Creating window {0} ({1}, {2})", windowProps.title, windowProps.width, windowProps.height);
			windowInterface = VE::Core::Scope<IWindow>(IWindow::create());
			if (!windowInterface) 
			{
				VE_CORE_ERROR("Failed to create window interface");
			}
			if (!windowInterface->initialize(windowProps)) 
			{
				VE_CORE_ERROR("Failed to create window backend");
			}
			windowInterface->setEventCallback(BIND_EVENT_FN(onEvent));

			// imguiLayer = new ImGuiLayer();
			// pushOverlay(imguiLayer);
		}

		Application::~Application()
		{
			// popOverlay(imguiLayer);
			// delete imguiLayer;

			if (!layer_stack.empty()) 
			{
				// TODO: Raise warning.
			}

			instance = nullptr;
		}

		void Application::execute()
		{
			while (running)
			{
				double timeMs = timer.getTime();

				Timestep deltaTime = timeMs - lastFrameTimeMs;
				Timestep timeStamp = timeMs;

				lastFrameTimeMs = timeMs;

				if (!minimized)
				{
					for (Layer* layer : layer_stack)
					{
						layer->onUpdate(deltaTime, timeStamp.toSeconds());
					}
				}

				/*
				imguiLayer->begin();
				for (Layer* layer : layer_stack)
				{
					layer->onImGuiRender();
				}
				imguiLayer->end();
				*/

				windowInterface->onUpdate();
			}
		}

		void Application::onEvent(Event::Event& e)
		{
			Event::EventHandler handler(e);
			handler.execute<Event::WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
			handler.execute<Event::WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));
			handler.execute<Event::KeyPressedEvent>(BIND_EVENT_FN(onMouseCaptured));

			for (auto it = layer_stack.end(); it != layer_stack.begin(); )
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
			layer_stack.pushLayer(layer);
		}

		void Application::pushOverlay(Layer* layer)
		{
			layer_stack.pushOverlay(layer);
		}

		void Application::popLayer(Layer* layer)
		{
			layer_stack.popLayer(layer);
		}

		void Application::popOverlay(Layer* layer)
		{
			layer_stack.popOverlay(layer);
		}

		bool Application::onWindowClose(Event::WindowCloseEvent& e)
		{
			running = false;
			return true;
		}

		bool Application::onWindowResize(Event::WindowResizeEvent& e)
		{
			if (e.getWidth() == 0 || e.getHeight() == 0)
			{
				minimized = true;
				return false;
			}
			minimized = false;
			Rendering::Renderer::onWindowResize(e.getWidth(), e.getHeight());

			return false;
		}

		bool Application::onMouseCaptured(Event::KeyPressedEvent& e)
		{
			if (e.getKeyCode() == VE_KEY_TAB)
			{
				windowInterface->toggleCaptureMouse();
			}
			if (e.getKeyCode() == VE_KEY_F)
			{
				windowInterface->toggleFullscreen();
				if (windowInterface->isFullscreen())
				{
					Rendering::Renderer::onWindowResize(windowInterface->getMonitorWidth(), windowInterface->getMonitorHeight());
				}
				else
				{
					Rendering::Renderer::onWindowResize(windowInterface->getWidth(), windowInterface->getHeight());
				}
			}
			if (e.getKeyCode() == VE_KEY_ESCAPE)
			{
				running = false;
				return true;
			}

			return false;
		}
	}
}
