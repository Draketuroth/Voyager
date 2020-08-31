#ifndef VE_RENDERJOB_H
#define VE_RENDERJOB_H

#include "Voyager/Core/Core.h"

#include "Voyager/Renderer/RenderSettings.h"

#include "Voyager/Renderer/Material.h"
#include "Voyager/Renderer/Geometry.h"
#include "Voyager/Renderer/Transform.h"
#include "Voyager/Renderer/Pipeline.h"

namespace VE 
{
	namespace Rendering 
	{
		struct VOYAGER_API Renderable 
		{
			Material* material;
			Geometry* geometry;
			Transform* transform;

			RenderMode renderMode = RenderMode::TEXTURED;
		};

		class VOYAGER_API RenderJob 
		{
		public:
			RenderJob() = delete;
			RenderJob(std::vector<Renderable> renderables, unsigned int pId);

			unsigned int getPipelineId() const;
			const std::vector<Renderable>& getRenderables();

		private:
			unsigned int _pipelineId;
			std::uint8_t _threadId;

			std::vector<Renderable> _renderables;
		};
	}
}

#endif