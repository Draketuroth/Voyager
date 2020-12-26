
#include "Voyager/Renderer/Texture.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/Renderer/OpenGL/OpenGLTexture.h"

#include "Platform/Renderer/RendererAPIHandler.h"
#include "Platform/APIType.h"

#include "Voyager/IO/Parsing.h"

namespace VE 
{
	namespace Rendering 
	{
		void Texture2D::createResource(Texture2D** resource, const std::string path = "./", VE::IO::Setting flags = VE::IO::Setting::None)
		{
			bool flip = (flags & VE::IO::Setting::FlipTexture) ? true : false;
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None:
					VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
					break;
				case Platform::API::RenderAPI::OpenGL:
					*resource = new Platform::OpenGL::OpenGLTexture2D(VE::IO::readImage(path, flip));
					break;
			}
		}

		Texture2D* Texture2D::create(const VE::Image::ImageData& data)
		{
			switch (Platform::Renderer::RendererAPIHandler::getAPI())
			{
				case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RenderAPI::None is not supported!");
				case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLTexture2D(data);
			}

			VE_CORE_ASSERT(false, "Unknown RenderAPI!");
			return nullptr;
		}
	}
}