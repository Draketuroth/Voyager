
#include "VoyagerIG/Layers/SceneLayer.h"
#include "VoyagerIG/Scene.h"

#include "Voyager/Components/Material.h"
#include "Voyager/Components/Geometry.h"
#include "Voyager/Components/Transform.h"

#include "Voyager/Core/Input.h"
#include "Voyager/Core/KeyCodes.h"

#include "Voyager/Event/EntityEvent.h"
#include "Voyager/Event/ComponentEvent.h"
#include "Voyager/Event/MouseEvent.h"
#include "Voyager/Event/KeyEvent.h"

#include "Platform/OpenGL/OpenGLTexture.h"

#include "Voyager/Renderer/Renderer.h"

#include "Voyager/IO/JSONParser.h"
#include "Voyager/IO/Parsing.h"

#include <algorithm>

#include <imgui.h>
#include <glad/glad.h>

static bool showEntityWidget = false;
static bool showAboutWidget = false;

VE::Rendering::RendererAPI::API api = VE::Rendering::Renderer::getAPI();

namespace IG
{
	SceneLayer::SceneLayer(Scene* scene): Layer("Scene")
	{
		_scene = scene;

		_scene->registerComponent<VE::Components::Transform>();
		_scene->registerComponent<VE::Components::Material>();
		_scene->registerComponent<VE::Components::Geometry>();

		_scene->_dispatcher->subscribe(VE::Event::EventType::VE_ENTITY_CREATED, std::bind(&SceneLayer::onEvent, this, std::placeholders::_1));
		_scene->_dispatcher->subscribe(VE::Event::EventType::VE_ENTITY_DESTROYED, std::bind(&SceneLayer::onEvent, this, std::placeholders::_1));

		_scene->_dispatcher->subscribe(VE::Event::EventType::VE_COMPONENT_ADDED, std::bind(&SceneLayer::onEvent, this, std::placeholders::_1));
		_scene->_dispatcher->subscribe(VE::Event::EventType::VE_COMPONENT_REMOVED, std::bind(&SceneLayer::onEvent, this, std::placeholders::_1));

		_logo = VE::Rendering::Texture2D::create(VE::IO::readImage("Textures\\logo.png", false));
	}

	SceneLayer::~SceneLayer()
	{

	}
	void SceneLayer::onUpdate(VE::Core::Timestep ts)
	{
		{
			if (!_imGuiMenuActive)
			{
				if (VE::Core::Input::isKeyPressed(VE_KEY_A))
				{
					_scene->_camera.moveLeft(ts);
				}
				if (VE::Core::Input::isKeyPressed(VE_KEY_D))
				{
					_scene->_camera.moveRight(ts);
				}
				if (VE::Core::Input::isKeyPressed(VE_KEY_S))
				{
					_scene->_camera.moveBackward(ts);
				}
				if (VE::Core::Input::isKeyPressed(VE_KEY_W))
				{
					_scene->_camera.moveForward(ts);
				}
				if (VE::Core::Input::isKeyPressed(VE_KEY_Q))
				{
					_scene->_camera.rotateCW(ts);
				}
				if (VE::Core::Input::isKeyPressed(VE_KEY_E))
				{
					_scene->_camera.rotateCCW(ts);
				}
			}

			_scene->_camera.update();
		}
	}
	void SceneLayer::onEvent(VE::Event::Event& event)
	{
		if (event.getEventType() == VE::Event::EventType::VE_ENTITY_CREATED)
		{
			VE::Event::EntityCreatedEvent& e = (VE::Event::EntityCreatedEvent&)event;
			VE_INFO("{0} from SceneLayer", e.toString().c_str());
		}

		if (event.getEventType() == VE::Event::EventType::VE_ENTITY_DESTROYED)
		{
			VE::Event::EntityDestroyedEvent& e = (VE::Event::EntityDestroyedEvent&)event;
			VE_INFO("{0} from SceneLayer", e.toString().c_str());

			VE::Core::Entity entity = e.getEntityId();

			_scene->_entityManager->destroyEntity(entity);
			_scene->_componentManager->entityDestroyed(entity);
			_scene->_systemManager->entityDestroyed(entity);
		}

		if (event.getEventType() == VE::Event::EventType::VE_COMPONENT_ADDED)
		{
			VE::Event::ComponentAddedEvent& e = (VE::Event::ComponentAddedEvent&)event;
			VE_INFO("{0}", e.toString().c_str());

			VE::Core::Entity entity = e.getEntityId();
			VE::Core::ComponentType type = e.getComponentType();

			auto signature = _scene->_entityManager->getSignature(entity);
			signature.set(type, true);

			_scene->_entityManager->setSignature(entity, signature);
			_scene->_systemManager->entitySignatureChanged(entity, signature);
		}

		if (event.getEventType() == VE::Event::EventType::VE_COMPONENT_REMOVED)
		{
			VE::Event::ComponentRemovedEvent& e = (VE::Event::ComponentRemovedEvent&)event;
			VE_INFO("{0}", e.toString().c_str());

			VE::Core::Entity entity = e.getEntityId();
			VE::Core::ComponentType type = e.getComponentType();

			auto signature = _scene->_entityManager->getSignature(entity);
			signature.set(type, false);
			_scene->_entityManager->setSignature(entity, signature);

			_scene->_systemManager->entitySignatureChanged(entity, signature);
		}

		if (event.getEventType() == VE::Event::EventType::VE_KEY_PRESSED)
		{
			VE::Event::KeyPressedEvent& e = (VE::Event::KeyPressedEvent&)event;
			if (e.getKeyCode() == VE_KEY_TAB)
			{
				_imGuiMenuActive = !_imGuiMenuActive;
			}
		}
		if (event.getEventType() == VE::Event::EventType::VE_MOUSE_MOVED)
		{
			VE::Event::MouseMovedEvent& e = (VE::Event::MouseMovedEvent&)event;
			if (!_imGuiMenuActive)
			{
				_scene->_camera.mouseUpdate(VE::Math::Vector2D(e.getXCoord(), e.getYCoord()));
			}
		}
	}

	void SceneLayer::showEntityWidgetFunc(bool* status)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("Entities", status))
		{
			ImGui::End();
			return;
		}

		if (ImGui::Button("Add Entity"))
		{
			_scene->createEntity();
		}

		if (_scene->_entities.size() > 0)
		{
			if (ImGui::TreeNode("Entities"))
			{
				for (auto& entity : _scene->_entities)
				{
					// Push entity id in order to use same labels without collisions in each entity drop down.
					ImGui::PushID(std::to_string(entity.id).c_str());

					std::string label = "Entity " + std::to_string(entity.id);
					if (ImGui::CollapsingHeader(label.c_str(), ImGuiTreeNodeFlags_None))
					{
						ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
						if (ImGui::BeginTabBar("Components", tab_bar_flags))
						{
							if (ImGui::BeginTabItem("Transform"))
							{
								auto& transform = _scene->getComponent<VE::Components::Transform>(entity.id);
								VE::Math::Vector3D pos = transform.getPosition();
								VE::Math::Vector3D scale = transform.getScale();
								VE::Math::YawPitchRoll rot = transform.getYawPitchRoll();

								// Position.
								ImGui::DragScalar("Pos X", ImGuiDataType_Float, &pos.x, 0.005f);
								ImGui::DragScalar("Pos Y", ImGuiDataType_Float, &pos.y, 0.005f);
								ImGui::DragScalar("Pos Z", ImGuiDataType_Float, &pos.z, 0.005f);
								transform.setPosition(pos);

								// Rotation
								ImGui::DragScalar("Yaw", ImGuiDataType_Float, &rot.yaw, 0.005f);
								ImGui::DragScalar("Pitch", ImGuiDataType_Float, &rot.pitch, 0.005f);
								ImGui::DragScalar("Roll", ImGuiDataType_Float, &rot.roll, 0.005f);
								transform.setRotation(rot);

								// Scale.
								ImGui::DragScalar("Scale X", ImGuiDataType_Float, &scale.x, 0.005f);
								ImGui::DragScalar("Scale Y", ImGuiDataType_Float, &scale.y, 0.005f);
								ImGui::DragScalar("Scale Z", ImGuiDataType_Float, &scale.z, 0.005f);
								transform.setScale(scale);

								ImGui::EndTabItem();
							}
							if (ImGui::BeginTabItem("Material")) 
							{
								auto& material = _scene->getComponent<VE::Components::Material>(entity.id);
								if (material.hasTexture(VE::Rendering::Material::TextureSlot::DIFFUSE) == false)
								{
									if (ImGui::Button("Add Diffuse"))
									{
										unsigned int handle = _scene->addTextureResource("TestTexture", "Textures\\1d9.png", VE::IO::Setting::FlipTexture);

										material.setTexture(_scene->getTextureResource(handle), VE::Rendering::Material::TextureSlot::DIFFUSE);
									}
									ImGui::EndTabItem();
								}
								else 
								{
									if (ImGui::Button("Remove Diffuse"))
									{
										auto diffuseTextureResource = material.getTexture(VE::Rendering::Material::TextureSlot::DIFFUSE);

										// Reset diffuse
										if (api == VE::Rendering::RendererAPI::API::OpenGL)
										{
											static_cast<VE::Platform::OpenGL::OpenGLTexture2D*>(diffuseTextureResource)->reset(0);
										}

										_scene->removeTextureResource(diffuseTextureResource->getHandle());
										material.resetTextureSlot(VE::Rendering::Material::TextureSlot::DIFFUSE);
									}
									ImGui::EndTabItem();
								}
							}
							if (ImGui::BeginTabItem("Geometry"))
							{
								auto& geometry = _scene->getComponent<VE::Components::Geometry>(entity.id);

								if (ImGui::Button("Toggle Wireframe"))
								{
									entity.wireframe = !entity.wireframe;
								}

								ImGui::EndTabItem();
							}
							ImGui::EndTabBar();
						}
					}
					ImGui::PopID();
				}
				ImGui::TreePop();
			}
		}

		ImGui::End();
	}
	void SceneLayer::showAboutWidgetFunc(bool* status)
	{
		ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
		if (!ImGui::Begin("About", status))
		{
			ImGui::End();
			return;
		}

		ImGui::Text("Voyager Engine v. 1.0");
		ImGui::Separator();
		ImGui::Text("By Fredrik Linde");

		GLuint texId = static_cast<VE::Platform::OpenGL::OpenGLTexture2D*>(_logo)->getTextureId();
		ImGui::Image((void*)(intptr_t)texId, ImVec2(_logo->getWidth(), _logo->getHeight()));

		ImGui::End();
	}
	void SceneLayer::onImGuiRender()
	{
		if (_imGuiMenuActive)
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("Widgets"))
				{
					ImGui::MenuItem("Entity Graph", NULL, &showEntityWidget);
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Help"))
				{
					ImGui::MenuItem("About", NULL, &showAboutWidget);
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			if (showEntityWidget) { showEntityWidgetFunc(&showEntityWidget); }
			if (showAboutWidget) { showAboutWidgetFunc(&showAboutWidget); }
		}
	}
}