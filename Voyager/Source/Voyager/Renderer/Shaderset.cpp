
#include "Voyager/Renderer/Renderer.h"
#include "Voyager/Renderer/Shaderset.h"
#include "Platform/OpenGL/OpenGLShaderset.h"

namespace VE 
{
	namespace Rendering
	{
		ShaderSet* ShaderSet::create(std::vector<Rendering::Shader*> shaders)
		{
			switch (Renderer::getAPI())
			{
			case RendererAPI::API::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
			case RendererAPI::API::OpenGL: return new Platform::OpenGL::OpenGLShaderSet(shaders);
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
}