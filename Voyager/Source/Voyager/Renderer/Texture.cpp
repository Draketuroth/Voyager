
#include "Voyager/Renderer/Texture.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "Voyager/IO/Parsing.h"

namespace VE 
{
	namespace Rendering 
	{
		void Texture2D::createResource(Texture2D** resource, const std::string path = "./", VE::IO::Setting flags = VE::IO::Setting::None)
		{
			bool flip = (flags & VE::IO::Setting::FlipTexture) ? true : false;
			switch (Renderer::getAPI())
			{
				case RendererAPI::API::None: 
					VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
					break;
				case RendererAPI::API::OpenGL: 
					*resource = new Platform::OpenGL::OpenGLTexture2D(VE::IO::readImage(path, flip));
					break;
			}
		}

		Texture2D* Texture2D::create(const VE::Image::ImageData& data)
		{
			switch (Renderer::getAPI())
			{
				case RendererAPI::API::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case RendererAPI::API::OpenGL: return new Platform::OpenGL::OpenGLTexture2D(data);
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}