
#include "VoyagerIG/Systems/RenderSystem.h"

#include "VoyagerIG/Scene.h"

#include "Voyager/Components/Transform.h"
#include "Voyager/Components/Material.h"
#include "Voyager/Components/Geometry.h"

namespace IG 
{
	std::vector<VE::Rendering::Renderable> RenderSystem::update(Scene* scene, VE::Core::Timestep ts)
	{
		std::vector<VE::Rendering::Renderable> renderables;
		for (auto entity : scene->_entities)
		{
			auto& transform = scene->getComponent<VE::Components::Transform>(entity.id);
			transform.update();

			VE::Rendering::Renderable renderable;

			renderable.renderMode = entity.wireframe ? VE::Rendering::RenderMode::WIREFRAME : VE::Rendering::RenderMode::TEXTURED;

			auto& material = scene->getComponent<VE::Components::Material>(entity.id);
			auto& geometry = scene->getComponent<VE::Components::Geometry>(entity.id);

			renderable.material = material.getMaterial();
			renderable.geometry = geometry.getGeometry();
			renderable.transform = transform.getTransform();

			renderables.push_back(renderable);
		}
		return renderables;
	}
}