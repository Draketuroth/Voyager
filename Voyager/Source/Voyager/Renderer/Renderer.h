#ifndef VE_RENDERER_H
#define VE_RENDERER_H

#include "Voyager/Renderer/RenderCommand.h"

#include "Voyager/Renderer/Camera.h"
#include "Voyager/Renderer/Pipeline.h"
#include "Voyager/Renderer/Transform.h"
#include "Voyager/Renderer/RenderJob.h"

#include "Voyager/Math/Matrix/Matrix4D.h"
#include "Voyager/Math/Vector/VectorLayout.h"

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

			static void beginScene(Core::Camera& camera, VE::Core::Timestep timeMs);
			static void endScene();

			static void submit(RenderJob& renderJob);

			static void registerPipeline(unsigned int pipelineId);

			static Pipeline* getPipeline(unsigned int pipelineId);

			inline static RendererAPI::API getAPI() { return RendererAPI::GetAPI(); }

			struct SceneData
			{
				VE::Math::Vector::LayoutXYZW eye;
				VE::Math::Vector::LayoutXYZW center;
				VE::Math::Matrix4D viewMatrix;
				VE::Math::Matrix4D projectionMatrix;
				VE::Math::Matrix4D viewProjectionMatrix;
			};
			struct DisplayData 
			{
				VE::Math::Vector::LayoutXY resolution;
			};
			struct TimeData 
			{
				float timeSec;
			};
		private:

			static VE::Core::Scope<std::unordered_map<unsigned int, Pipeline*>> _pipelines;
			static VE::Core::Scope<std::vector<RenderJob>> _renderJobs;
		};
	}
};

#endif