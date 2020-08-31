
#include "Voyager/Renderer/RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace VE
{
	namespace Rendering 
	{
		RendererAPI* RenderCommand::_renderAPI = new Platform::OpenGL::OpenGLRendererAPI;
	}
};