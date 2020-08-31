#include "RenderJob.h"

namespace VE 
{
	namespace Rendering 
	{
		RenderJob::RenderJob(std::vector<Renderable> renderables, unsigned int pId) : _pipelineId(pId)
		{
			_renderables.reserve(renderables.size());
			_renderables.insert(std::end(_renderables), std::begin(renderables), std::end(renderables));
		}
		unsigned int RenderJob::getPipelineId() const
		{
			return _pipelineId;
		}
		const std::vector<Renderable>& RenderJob::getRenderables()
		{
			return _renderables;
		}
	}
}