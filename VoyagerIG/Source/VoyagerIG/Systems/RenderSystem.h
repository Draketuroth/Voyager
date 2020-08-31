#ifndef VE_RENDER_SYSTEM_H
#define VE_RENDER_SYSTEM_H

#include "Voyager/Core/System.h"
#include "Voyager/Core/Timestep.h"

#include "Voyager/Renderer/RenderJob.h"

namespace IG { class Scene; }

namespace IG 
{
	class RenderSystem : public VE::Core::System
	{
	public:
		std::vector<VE::Rendering::Renderable> update(Scene* scene, VE::Core::Timestep ts);
	};
}


#endif