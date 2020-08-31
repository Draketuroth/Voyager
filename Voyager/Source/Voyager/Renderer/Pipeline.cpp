
#include "Voyager/Renderer/Pipeline.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLPipeline.h"

namespace VE 
{
	namespace Rendering
	{
		Pipeline* Pipeline::create()
		{
			switch (Renderer::getAPI())
			{
				case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
				case RendererAPI::API::OpenGL: return new Platform::OpenGL::OpenGLPipeline();
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}
