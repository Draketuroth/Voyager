#ifndef VE_RENDERER_H
#define VE_RENDERER_H

#include "Voyager/Renderer/RenderCommand.h"

#include "Voyager/Renderer/Camera.h"
#include "Voyager/Renderer/Pipeline.h"
#include "Voyager/Renderer/Transform.h"
#include "Voyager/Renderer/RenderJob.h"

#include "Voyager/Math/Matrix/Matrix4D.h"

#include <glad/glad.h>

namespace VE
{
	namespace Rendering 
	{
		class Pipeline;

		class VOYAGER_API Renderer
		{
		public:
			static void onWindowResize(std::uint32_t width, std::uint32_t height);

			static void beginScene(Core::Camera& camera);
			static void endScene();

			static void submit(RenderJob& renderJob);

			static void registerPipeline(unsigned int pipelineId);

			static Pipeline* getPipeline(unsigned int pipelineId);

			inline static RendererAPI::API getAPI() { return RendererAPI::GetAPI(); }

			struct SceneData
			{
				VE::Math::Vector4D eye;
				VE::Math::Vector4D center;
				VE::Math::Matrix4D viewMatrix;
				VE::Math::Matrix4D projectionMatrix;
				VE::Math::Matrix4D viewProjectionMatrix;
			};
			struct DisplayData 
			{
				VE::Math::Vector2D resolution;
			};
		private:

			static std::unordered_map<unsigned int, Pipeline*>* _pipelines;
			static std::vector<RenderJob>* _renderJobs;
		};
	}
};

#endif