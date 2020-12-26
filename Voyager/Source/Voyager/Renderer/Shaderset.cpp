
#include "Voyager/Renderer/Renderer.h"
#include "Voyager/Renderer/Shaderset.h"
#include "Platform/Renderer/OpenGL/OpenGLShaderset.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/APIType.h"

namespace VE 
{
	namespace Rendering
	{
		ShaderSet* ShaderSet::create(std::vector<Rendering::Shader*> shaders)
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
			case Platform::API::RenderAPI::None: 
				VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
				break;
			case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLShaderSet(shaders);
			}
			return nullptr;
		}
	}
}