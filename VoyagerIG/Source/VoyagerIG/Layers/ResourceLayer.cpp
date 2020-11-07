
#include "VoyagerIG/Layers/ResourceLayer.h"
#include "VoyagerIG/Scene.h"

#include "Voyager/Components/Transform.h"
#include "Voyager/Components/Material.h"
#include "Voyager/Components/Geometry.h"

#include "Voyager/Math/Vector/Vector2.h"

#include "Voyager/Renderer/Renderer.h"
#include "Voyager/Renderer/Identifier.h"

#include "Voyager/Event/ApplicationEvent.h"

#include "Voyager/IO/JSONParser.h"
#include "Voyager/IO/OBJParser.h"

namespace IG
{
	ResourceLayer::ResourceLayer(Scene* scene, unsigned int winSizeX, unsigned int winSizeY) : Layer("Resource")
	{
		_scene = scene;

		VE::Core::Scope<VE::Event::Dispatcher> fileDispatcher(VE::Event::IDispatcher::create());
		fileDispatcher->subscribe(VE::Event::EventType::VE_FILE_CREATED, std::bind(&ResourceLayer::onEvent, this, std::placeholders::_1));
		fileDispatcher->subscribe(VE::Event::EventType::VE_FILE_DELETED, std::bind(&ResourceLayer::onEvent, this, std::placeholders::_1));
		fileDispatcher->subscribe(VE::Event::EventType::VE_FILE_MODIFIED, std::bind(&ResourceLayer::onEvent, this, std::placeholders::_1));
		_fileNotifier.reset(VE::IO::IFileNotifier::create("Shaders", std::move(fileDispatcher)));

		VE::Geometry::GeometryData data = VE::IO::OBJ::parse("Models\\Sandshark.obj");

		int geometryHandle = _scene->addGeometryResource("TestPlane");
		auto geometryRes = _scene->getGeometryResource(geometryHandle);

		VE::Core::Ref<VE::Rendering::VertexBuffer> squareVB;
		squareVB.reset(VE::Rendering::VertexBuffer::create(data.vertices.data(), sizeof(float) * data.vertices.size(), data.vertices.size()));
		squareVB->setLayout({
			 { VE::Rendering::ShaderDataType::Float3, "vertex_position"} ,
			 { VE::Rendering::ShaderDataType::Float3, "vertex_normal"} ,
			 { VE::Rendering::ShaderDataType::Float3, "vertex_barycentric"} ,
			 { VE::Rendering::ShaderDataType::Float2, "vertex_texcoord"}
			});
		geometryRes->setVertexBuffer(squareVB);

		unsigned int simplePipelineId = VE::Rendering::Identifier::get("Simple", VE::Rendering::Identifier::IdentifierType::PIPELINE);
		unsigned int sceneDataBufferId = VE::Rendering::Identifier::get("SceneData", VE::Rendering::Identifier::IdentifierType::BUFFER);
		unsigned int displayDataBufferId = VE::Rendering::Identifier::get("DisplayData", VE::Rendering::Identifier::IdentifierType::BUFFER);
		unsigned int timeDataBufferId = VE::Rendering::Identifier::get("TimeData", VE::Rendering::Identifier::IdentifierType::BUFFER);

		VE::Rendering::Renderer::registerPipeline(simplePipelineId);
		VE::Rendering::Pipeline* simplePipeline = VE::Rendering::Renderer::getPipeline(simplePipelineId);
		if (simplePipeline)
		{
			simplePipeline->createSharedBuffer(sceneDataBufferId, sizeof(VE::Rendering::Renderer::SceneData));
			simplePipeline->createSharedBuffer(displayDataBufferId, sizeof(VE::Rendering::Renderer::DisplayData));
			simplePipeline->createSharedBuffer(timeDataBufferId, sizeof(VE::Rendering::Renderer::TimeData));

			simplePipeline->createRenderTarget(VE::Rendering::Identifier::get("FrameBuffer", VE::Rendering::Identifier::IdentifierType::RENDERTARGET), winSizeX, winSizeY);

			VE::Rendering::Renderer::DisplayData displayData;
			displayData.resolution = VE::Math::Vector2(static_cast<float>(winSizeX), static_cast<float>(winSizeY));
			simplePipeline->updateSharedBuffer(VE::Rendering::Identifier::get("DisplayData", VE::Rendering::Identifier::IdentifierType::BUFFER), sizeof(VE::Rendering::Renderer::DisplayData), &displayData);

			VE::Rendering::Renderer::TimeData timeData;
			timeData.timeSec = 0.0f;
			simplePipeline->updateSharedBuffer(VE::Rendering::Identifier::get("TimeData", VE::Rendering::Identifier::IdentifierType::BUFFER), sizeof(VE::Rendering::Renderer::TimeData), &timeData);
		}

		std::string shaderSetConfigPath = "Config\\Shadersets.json";
		std::string buffer = VE::IO::readFileToString(shaderSetConfigPath);

		std::string errorCode;
		auto shaderSetConfig = VE::IO::JSON::JSONNode::parse(buffer, errorCode, VE::IO::JSON::JSONParseStrategy::COMMENTS);
		if (!shaderSetConfig.isNull())
		{
			auto shadersets = shaderSetConfig["shadersets"].asArray();
			for (auto shaderset : shadersets) 
			{
				std::string shadersetName = shaderset["name"].asString();
				std::string renderPass = shaderset["renderpass"].asString();

				auto shaders = shaderset["shaders"].asArray();

				std::vector<VE::Rendering::Shader*> shadervec;
				for (auto shader : shaders) 
				{
					std::string shaderPath = shader["path"].asString();
					std::string shaderFile = shader["file"].asString();
					shaderPath.append(shaderFile);

					_scene->_shaderPipelineMap.insert({ shaderPath, shadersetName });

					shadervec.push_back(VE::Rendering::Shader::create(shaderPath));
				}

				VE::Rendering::ShaderSet* shaderSet = VE::Rendering::ShaderSet::create(shadervec);

				unsigned int shadersetId = VE::Rendering::Identifier::get(shadersetName, VE::Rendering::Identifier::IdentifierType::SHADERSET);
				simplePipeline->attachShaderset(shadersetId, shaderSet);
				simplePipeline->registerToBuffer(shadersetId, sceneDataBufferId, 0);
				simplePipeline->registerToBuffer(shadersetId, displayDataBufferId, 1);
				simplePipeline->registerToBuffer(shadersetId, timeDataBufferId, 2);
			}
		}
		else
		{
			VE_CORE_WARN("Failed reading Shadersets.json, pipeline setup not complete. Error: " + errorCode);
			exit(0);
		}
	}

	ResourceLayer::~ResourceLayer()
	{
		_scene = nullptr;
	}

	void ResourceLayer::onUpdate(VE::Core::Timestep delta, VE::Core::Timestep timeMs)
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
	}

	void ResourceLayer::onEvent(VE::Event::Event& event)
	{
		if (event.getEventType() == VE::Event::EventType::VE_WINDOW_RESIZE) 
		{
			VE::Event::WindowResizeEvent& e = (VE::Event::WindowResizeEvent&)event;
		}

		if (event.getEventType() == VE::Event::EventType::VE_FILE_CREATED)
		{
			VE::Event::FileCreatedEvent& e = (VE::Event::FileCreatedEvent&)event;
			VE_INFO("{0} from SceneLayer", e.toString().c_str());
		}

		if (event.getEventType() == VE::Event::EventType::VE_FILE_DELETED)
		{
			VE::Event::FileDeletedEvent& e = (VE::Event::FileDeletedEvent&)event;
			VE_INFO("{0} from SceneLayer", e.toString().c_str());
		}

		if (event.getEventType() == VE::Event::EventType::VE_FILE_MODIFIED)
		{
			VE::Event::FileModifiedEvent& e = (VE::Event::FileModifiedEvent&)event;
			VE_INFO("{0} from SceneLayer", e.toString().c_str());

			std::string filePath = e.getPath();

			// See if the file is part of a shaderset...
			auto shadersetIdentifer = _scene->_shaderPipelineMap.find(filePath);
			if (shadersetIdentifer != _scene->_shaderPipelineMap.end())
			{
				std::string shadersetName = shadersetIdentifer->second;

				std::string shaderSetConfigPath = "Config\\Shadersets.json";
				std::string buffer = VE::IO::readFileToString(shaderSetConfigPath);

				std::string errorCode;
				auto shaderSetConfig = VE::IO::JSON::JSONNode::parse(buffer, errorCode, VE::IO::JSON::JSONParseStrategy::COMMENTS);
				if (!shaderSetConfig.isNull())
				{
					// Read shaderset config and find index to shaderset from shader
					auto shadersets = shaderSetConfig["shadersets"].asArray();
					for (auto shaderset : shadersets)
					{
						if (shaderset["name"] == shadersetName)
						{
							auto shaders = shaderset["shaders"].asArray();
							auto layout = shaderset["layout"].asArray();

							std::vector<std::string> shadervec;
							for (auto shader : shaders)
							{
								std::string shaderPath = shader["path"].asString();
								std::string shaderFile = shader["file"].asString();
								shaderPath.append(shaderFile);

								shadervec.push_back(shaderPath);
							}
							_scene->_pipelineToRecompile.push_back({ shadervec, shadersetName });

							// VE::Rendering::ShaderSet* shaderSet = VE::Rendering::ShaderSet::create(shadervec);

							// VE::Rendering::Renderer::attachShaderset(shaderSetName.c_str(), shaderSet);
							break;
						}
					}
				}
			}
		}
	}
}