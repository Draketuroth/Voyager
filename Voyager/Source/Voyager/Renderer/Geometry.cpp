
#include "Voyager/Renderer/Geometry.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/Renderer/OpenGL/OpenGLVertexArray.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/APIType.h"

namespace VE
{
	namespace Rendering 
	{
		void Geometry::createResource(Geometry** resource, const std::string path, VE::IO::Setting flags)
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
			case Platform::API::RenderAPI::None:
				VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				break;
			case Platform::API::RenderAPI::OpenGL:
				*resource = new Platform::OpenGL::OpenGLVertexArray();
				break;
			}
		}
		Geometry* Geometry::create()
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLVertexArray();
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
};