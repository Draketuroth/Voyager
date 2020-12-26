
#include "Voyager/Renderer/Pipeline.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/Renderer/OpenGL/OpenGLPipeline.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/APIType.h"

namespace VE 
{
	namespace Rendering
	{
		Pipeline* Pipeline::create()
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLPipeline();
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}
