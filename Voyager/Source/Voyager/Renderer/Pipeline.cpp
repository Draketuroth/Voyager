
#include "Voyager/Renderer/Pipeline.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLPipeline.h"

#include "Platform/APIType.h"

namespace VE 
{
	namespace Rendering
	{
		Pipeline* Pipeline::create()
		{
			switch (Renderer::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLPipeline();
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}
