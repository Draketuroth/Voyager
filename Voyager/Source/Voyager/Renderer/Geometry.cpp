
#include "Voyager/Renderer/Geometry.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Platform/APIType.h"

namespace VE
{
	namespace Rendering 
	{
		void Geometry::createResource(Geometry** resource, const std::string path, VE::IO::Setting flags)
		{
			switch (Renderer::getAPI())
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
			switch (Renderer::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLVertexArray();
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
};