
#include "VoyagerIG/Scene.h"

#include "Voyager/Components/Geometry.h"
#include "Voyager/Components/Material.h"
#include "Voyager/Components/Transform.h"

#include "Voyager/Renderer/Identifier.h"

#include "Voyager/Event/EntityEvent.h"

#include <functional>

namespace IG
{
	Scene::Scene() : _camera()
	{
		_entityManager.reset(VE::Core::IEntityManager::create());
		_componentManager.reset(VE::Core::IComponentManager::create());
		_systemManager.reset(VE::Core::ISystemManager::create());

		_dispatcher.reset(VE::Event::IDispatcher::create());

		_entities.reserve(VE::Core::MAX_ENTITIES);

		{
			using namespace std::placeholders;
			_materialResourceManager.reset(new VE::Core::ResourceManager<VE::Rendering::Material>(std::bind(&IG::Scene::createMaterialResource, this, _1, _2, _3)));
			_textureResourceManager.reset(new VE::Core::ResourceManager<VE::Rendering::Texture2D>(std::bind(&IG::Scene::createTextureResource, this, _1, _2, _3)));
			_geometryResourceManager.reset(new VE::Core::ResourceManager<VE::Rendering::Geometry>(std::bind(&IG::Scene::createGeometryResource, this, _1, _2, _3)));
			_shaderResourceManager.reset(new VE::Core::ResourceManager<VE::Rendering::Shader>(std::bind(&IG::Scene::createShaderResource, this, _1, _2, _3)));
		}
	}
	Scene::~Scene()
	{
		
	}

	VE::Core::Entity Scene::createEntity()
	{
		VE::Core::EntityInfo entityData;
		entityData.id = _entityManager->createEntity();
		_entities.push_back(entityData);

		addComponent(entityData.id, VE::Components::Transform());
		addComponent(entityData.id, VE::Components::Material());
		addComponent(entityData.id, VE::Components::Geometry());

		unsigned int materialHandle = addMaterialResource("TestMaterial");

		auto& material = getComponent<VE::Components::Material>(entityData.id);
		material.setMaterialResourcePointer(_materialResourceManager->getElement("TestMaterial"));
		material.setShaderIdentifier(VE::Rendering::Identifier::get("TexturedMaterial", VE::Rendering::Identifier::IdentifierType::SHADERSET));

		auto& geometry = getComponent<VE::Components::Geometry>(entityData.id);
		geometry.setGeometryResourcePointer(_geometryResourceManager->getElement("TestPlane"));

		VE::Event::EntityCreatedEvent event(entityData.id);
		_dispatcher->post(event);

		return entityData.id;
	}

	void Scene::destroyEntity(VE::Core::Entity entity)
	{
		VE::Event::EntityDestroyedEvent event(entity);
		_dispatcher->post(event);
	}
	void Scene::createMaterialResource(VE::Rendering::Material** material, const std::string path, VE::IO::Setting flags)
	{
		VE::Rendering::Material::createResource(material, path, flags);
	}
	void Scene::createTextureResource(VE::Rendering::Texture2D** texture, const std::string path = "./", VE::IO::Setting flags = VE::IO::Setting::None)
	{
		VE::Rendering::Texture2D::createResource(texture, path, flags);
	}
	void Scene::createGeometryResource(VE::Rendering::Geometry** texture, const std::string path = "./", VE::IO::Setting flags = VE::IO::Setting::None)
	{
		VE::Rendering::Geometry::createResource(texture, path, flags);
	}
	void Scene::createShaderResource(VE::Rendering::Shader** shader, const std::string path, VE::IO::Setting flags)
	{
		VE::Rendering::Shader::createResource(shader, path, flags);
	}
}
