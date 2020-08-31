#include "Voyager/Renderer/Transform.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTransform.h"

namespace VE
{
	namespace Rendering
	{
		Transform* Transform::create()
		{
			switch (Renderer::getAPI())
			{
				case RendererAPI::API::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case RendererAPI::API::OpenGL: return new Platform::OpenGL::OpenGLTransform();
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}