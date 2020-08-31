#ifndef IG_SCENE_H
#define IG_SCENE_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Types.h"
#include "Voyager/Core/EntityManager.h"
#include "Voyager/Core/ComponentManager.h"
#include "Voyager/Core/SystemManager.h"
#include "Voyager/Core/ResourceManager.h"

#include "Voyager/Event/Dispatcher.h"
#include "Voyager/Event/ComponentEvent.h"

#include "Voyager/Renderer/Shader.h"
#include "Voyager/Renderer/Pipeline.h"
#include "Voyager/Renderer/PerspectiveCamera.h"

#include "Voyager/Renderer/Texture.h"
#include "Voyager/Renderer/Geometry.h"
#include "Voyager/Renderer/Material.h"

namespace IG
{
	class Scene
	{
		friend class SceneLayer;
		friend class ResourceLayer;
		friend class RenderLayer;
		friend class RenderSystem;
	public:
		Scene();
		~Scene();

		template<typename T>
		void registerComponent() 
		{
			_componentManager->registerComponent<T>();
		}

		template<typename T>
		void addComponent(VE::Core::Entity entity, T component)
		{
			_componentManager->addComponent<T>(entity, component);
			VE::Event::ComponentAddedEvent event(_componentManager->getComponentType<T>(), entity);
			_dispatcher->post(event);
		}

		template<typename T>
		void removeComponent(VE::Core::Entity entity)
		{
			_componentManager->removeComponent<T>(entity);
			VE::Event::ComponentRemovedEvent event(_componentManager->getComponentType<T>(), entity);
			_dispatcher->post(event);
		}


		template<typename T>
		T& getComponent(VE::Core::Entity entity)
		{
			return _componentManager->getComponent<T>(entity);
		}

		template<typename T>
		VE::Core::ComponentType getComponentType()
		{
			return _componentManager->getComponentType<T>();
		}

		template<typename T>
		VE::Core::Ref<T> registerSystem()
		{
			return _systemManager->registerSystem<T>();
		}

		template<typename T>
		void setSystemSignature(VE::Core::Signature signature)
		{
			_systemManager->setSignature<T>(signature);
		}

		unsigned int addMaterialResource(const std::string& name, const std::string& path = "./", VE::IO::Setting flags = VE::IO::Setting::None) 
		{
			return _materialResourceManager->add(name, path, flags);
		}

		unsigned int addTextureResource(const std::string& name, const std::string& path = "./", VE::IO::Setting flags = VE::IO::Setting::None) 
		{
			return _textureResourceManager->add(name, path, flags);
		}

		unsigned int addGeometryResource(const std::string& name, const std::string& path = "./", VE::IO::Setting flags = VE::IO::Setting::None) 
		{
			return _geometryResourceManager->add(name, path, flags);
		}

		void removeTextureResource(unsigned int handle)
		{
			return _textureResourceManager->remove(handle);
		}

		void removeGeometryResource(unsigned int handle) 
		{
			return _geometryResourceManager->remove(handle);
		}

		VE::Rendering::Material* getMaterialResource(unsigned int handle) 
		{
			return _materialResourceManager->getElement(handle);
		}

		VE::Rendering::Texture2D* getTextureResource(unsigned int handle) 
		{
			return _textureResourceManager->getElement(handle);
		}

		VE::Rendering::Geometry* getGeometryResource(unsigned int handle) 
		{
			return _geometryResourceManager->getElement(handle);
		}

		VE::Core::Entity createEntity();

		void destroyEntity(VE::Core::Entity entity);

	private:

		void createMaterialResource(VE::Rendering::Material** material, const std::string path, VE::IO::Setting flags);
		void createTextureResource(VE::Rendering::Texture2D** texture, const std::string path, VE::IO::Setting flags);
		void createGeometryResource(VE::Rendering::Geometry** geometry, const std::string path, VE::IO::Setting flags);
		void createShaderResource(VE::Rendering::Shader** shader, const std::string path, VE::IO::Setting flags);

		VE::Core::Scope<VE::Event::Dispatcher> _dispatcher;

		VE::Core::Scope<VE::Core::EntityManager> _entityManager;
		VE::Core::Scope<VE::Core::ComponentManager> _componentManager;
		VE::Core::Scope<VE::Core::SystemManager> _systemManager;

		VE::Core::Scope<VE::Core::ResourceManager<VE::Rendering::Material>> _materialResourceManager;
		VE::Core::Scope<VE::Core::ResourceManager<VE::Rendering::Texture2D>> _textureResourceManager;
		VE::Core::Scope<VE::Core::ResourceManager<VE::Rendering::Geometry>> _geometryResourceManager;
		VE::Core::Scope<VE::Core::ResourceManager<VE::Rendering::Shader>> _shaderResourceManager;

		std::map<std::string, std::string> _shaderPipelineMap;
		std::vector <std::pair<std::vector<std::string>, std::string>> _pipelineToRecompile;

		VE::Rendering::PerspectiveCamera _camera;

		std::vector<VE::Core::EntityInfo> _entities;
	};
}

#endif