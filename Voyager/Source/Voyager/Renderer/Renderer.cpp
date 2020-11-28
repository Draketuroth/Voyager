
#include "Voyager/Renderer/Renderer.h"
#include "Voyager/Renderer/Pipeline.h"

#include "Voyager/Core/Log.h"

#include "Voyager/Renderer/Identifier.h"

#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "Voyager/Core/Bitmask.h"

namespace VE
{
	namespace Rendering 
	{
		VE::Core::Scope<std::vector<RenderJob>> Renderer::_renderJobs(new std::vector<RenderJob>);
		VE::Core::Scope <std::unordered_map<unsigned int, Pipeline*>> Renderer::_pipelines(new std::unordered_map<unsigned int, Pipeline*>);

		void Renderer::onWindowResize(std::uint32_t width, std::uint32_t height)
		{
			RenderCommand::setViewport(0, 0, width, height);

			DisplayData displayData;
			displayData.resolution = Math::Vector2(width, height);

			VE::Rendering::Pipeline* simplePipeline = getPipeline(VE::Rendering::Identifier::get("Simple", VE::Rendering::Identifier::IdentifierType::PIPELINE));
			if (simplePipeline)
			{
				simplePipeline->updateSharedBuffer(VE::Rendering::Identifier::get("DisplayData", VE::Rendering::Identifier::IdentifierType::BUFFER), sizeof(DisplayData), &displayData);
				simplePipeline->resizeRenderTarget(VE::Rendering::Identifier::get("FrameBuffer", Identifier::IdentifierType::RENDERTARGET), width, height);
			}
		}

		void Renderer::beginScene(Core::Camera& camera, VE::Core::Timestep timeMs)
		{
			SceneData sceneData;
			sceneData.eye = camera.getPosition();
			sceneData.center = camera.getDirection();
			sceneData.viewMatrix = camera.getViewMatrix();
			sceneData.projectionMatrix = camera.getProjectionMatrix();
			sceneData.viewProjectionMatrix = camera.getViewProjectionMatrix();

			TimeData timeData;
			timeData.timeSec = timeMs.toSecondsFloat();

			VE::Rendering::Pipeline* simplePipeline = getPipeline( VE::Rendering::Identifier::get("Simple", VE::Rendering::Identifier::IdentifierType::PIPELINE));
			if (simplePipeline) 
			{
				simplePipeline->updateSharedBuffer(VE::Rendering::Identifier::get("SceneData", VE::Rendering::Identifier::IdentifierType::BUFFER), sizeof(SceneData), &sceneData);
				simplePipeline->updateSharedBuffer(VE::Rendering::Identifier::get("TimeData", VE::Rendering::Identifier::IdentifierType::BUFFER), sizeof(TimeData), &timeData);
			}
		}

		void Renderer::endScene()
		{
			// Clear default framebuffer object.
			RenderCommand::clear(ClearFlags::COLOR | ClearFlags::DEPTH);

			for (RenderJob& renderJob : *_renderJobs) 
			{
				const unsigned int pipelineId = renderJob.getPipelineId();
				const std::vector<Renderable>& renderables = renderJob.getRenderables();

				Pipeline* pipeline = getPipeline(pipelineId);
				if (pipeline) 
				{
					pipeline->setActiveRenderTarget(VE::Rendering::Identifier::get("FrameBuffer", Identifier::IdentifierType::RENDERTARGET));
					RenderCommand::clear(ClearFlags::COLOR | ClearFlags::DEPTH);

					// Draw six vertices, vertex shader creates the quad.
					pipeline->setActiveShader(VE::Rendering::Identifier::get("GradientBackground", Identifier::IdentifierType::SHADERSET));
					RenderCommand::setDepthTest(false);
					RenderCommand::draw(6);
					RenderCommand::setDepthTest(true);

					for (const Renderable& renderable : renderables)
					{
						Material* material = renderable.material;
						if (material) 
						{
							Texture2D* diffuse = material->getTexture(VE::Rendering::Material::TextureSlot::DIFFUSE);
							if (getAPI() == VE::Rendering::RendererAPI::API::OpenGL)
							{
								if (diffuse)
								{
									static_cast<VE::Platform::OpenGL::OpenGLTexture2D*>(diffuse)->bind(0);
								}
							}

							unsigned int shaderId = material->getShaderIdentifier();
							pipeline->setActiveShader(shaderId);
							pipeline->updateConstantMatrix4x4("model_to_world", renderable.transform->getTransformMatrix(), true);
							pipeline->updateConstantInt("wireframe", static_cast<unsigned int>(renderable.renderMode));

							RenderCommand::draw(renderable.geometry);
							
					        pipeline->resetRenderTarget();
							RenderCommand::clear(ClearFlags::COLOR);
							
							pipeline->setActiveShader(VE::Rendering::Identifier::get("ScreenOutput", Identifier::IdentifierType::SHADERSET));
							RenderCommand::setDepthTest(false);
							pipeline->setColorAttachment(VE::Rendering::Identifier::get("FrameBuffer", Identifier::IdentifierType::RENDERTARGET));
							RenderCommand::draw(6);
							RenderCommand::setDepthTest(true);

						}
					}
				}
			}
			_renderJobs->clear();
		}

		void Renderer::submit(RenderJob& renderJob)
		{
			_renderJobs->push_back(renderJob);
		}

		void Renderer::registerPipeline(unsigned int pipelineId)
		{
			_pipelines->insert(std::make_pair(pipelineId, VE::Rendering::Pipeline::create()));
		}

		Pipeline* Renderer::getPipeline(unsigned int pipelineId)
		{
			std::unordered_map<unsigned int, Pipeline*>::iterator it = _pipelines->find(pipelineId);
			if (it != _pipelines->end())
			{
				return it->second;
			}
			return nullptr;
		}
	}
};