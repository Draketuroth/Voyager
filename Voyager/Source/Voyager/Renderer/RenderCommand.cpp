
#include "Voyager/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace VE
{
	namespace Rendering
	{
		RendererAPIHandler* RenderCommand::_renderAPI = new Platform::OpenGL::OpenGLRendererAPI;
	}
};