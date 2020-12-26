#include "Voyager/Renderer/Transform.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/Renderer/OpenGL/OpenGLTransform.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/APIType.h"

namespace VE
{
	namespace Rendering
	{
		Transform* Transform::create()
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLTransform();
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}