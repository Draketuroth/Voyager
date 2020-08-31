
#include "Voyager/Renderer/Geometry.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace VE
{
	namespace Rendering 
	{
		void Geometry::createResource(Geometry** resource, const std::string path, VE::IO::Setting flags)
		{
			switch (Renderer::getAPI())
			{
			case RendererAPI::API::None:
				VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				break;
			case RendererAPI::API::OpenGL:
				*resource = new Platform::OpenGL::OpenGLVertexArray();
				break;
			}
		}
		Geometry* Geometry::create()
		{
			switch (Renderer::getAPI())
			{
				case RendererAPI::API::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case RendererAPI::API::OpenGL: return new Platform::OpenGL::OpenGLVertexArray();
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
};