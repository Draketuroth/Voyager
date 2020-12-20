#include "Voyager/Renderer/Transform.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTransform.h"

#include "Platform/APIType.h"

namespace VE
{
	namespace Rendering
	{
		Transform* Transform::create()
		{
			switch (Renderer::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLTransform();
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}