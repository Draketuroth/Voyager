
#include "VoyagerIG/Layers/RenderLayer.h"
#include "VoyagerIG/Scene.h"

#include "Voyager/Components/Transform.h"
#include "Voyager/Components/Material.h"
#include "Voyager/Components/Geometry.h"

#include "Voyager/Renderer/Renderer.h"
#include "Voyager/Renderer/Identifier.h"

#include "Voyager/IO/JSONParser.h"
#include "Voyager/IO/OBJParser.h"

namespace IG
{
	RenderLayer::RenderLayer(Scene* scene) : Layer("Render")
	{
		_scene = scene;

		_renderSystem = _scene->registerSystem<RenderSystem>();

		VE::Core::Signature signature;
		signature.set(_scene->getComponentType<VE::Components::Transform>());
		_scene->setSystemSignature<RenderSystem>(signature);

		// Setup rendering related settings...
		VE::Rendering::RenderCommand::setClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		VE::Rendering::RenderCommand::setBackfaceCulling(true);
		VE::Rendering::RenderCommand::setDepthTest(true);
	}

	RenderLayer::~RenderLayer()
	{
		_scene = nullptr;
	}

	void RenderLayer::onUpdate(VE::Core::Timestep delta, VE::Core::Timestep timeMs)
	{
		if (_scene->_pipelineToRecompile.size() > 0) 
		{
			std::vector<VE::Rendering::Shader*> shadervec;
			for (auto pipeline : _scene->_pipelineToRecompile)
			{
				for (auto shader : pipeline.first) 
				{
					shadervec.push_back(VE::Rendering::Shader::create(shader));
				}
				
				VE::Rendering::ShaderSet* shaderSet = VE::Rendering::ShaderSet::create(shadervec);

				VE::Rendering::Pipeline* simplePipeline = VE::Rendering::Renderer::getPipeline(VE::Rendering::Identifier::get("Simple", VE::Rendering::Identifier::IdentifierType::PIPELINE));
				if (simplePipeline) 
				{
					simplePipeline->attachShaderset(VE::Rendering::Identifier::get(pipeline.second, VE::Rendering::Identifier::IdentifierType::SHADERSET), shaderSet);
				}
			}
			_scene->_pipelineToRecompile.clear();
		}

		VE::Rendering::Renderer::beginScene(_scene->_camera, timeMs);
		std::vector<VE::Rendering::Renderable> renderables = _renderSystem->update(_scene, delta);

		if (!renderables.empty()) 
		{
			VE::Rendering::RenderJob renderJob(renderables, VE::Rendering::Identifier::get("Simple", VE::Rendering::Identifier::IdentifierType::PIPELINE));
			VE::Rendering::Renderer::submit(renderJob);
		}

		VE::Rendering::Renderer::endScene();
	}

	void RenderLayer::onEvent(VE::Event::Event& event)
	{
		
	}
}

/*
	unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	VE::Core::Ref<VE::Rendering::IndexBuffer> squareIB;
	squareIB.reset(VE::Rendering::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int)));
	geometryRes->setIndexBuffer(squareIB);
*/