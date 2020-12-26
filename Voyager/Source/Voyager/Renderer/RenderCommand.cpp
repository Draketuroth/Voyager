
#include "Voyager/Renderer/RenderCommand.h"
#include "Platform/Renderer/OpenGL/OpenGLRendererAPI.h"

namespace VE
{
	namespace Rendering
	{
		RendererAPI* RenderCommand::_renderAPI = new Platform::OpenGL::OpenGLRendererAPI;
	}
};