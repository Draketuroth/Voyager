
#include "Voyager/Renderer/Buffer.h"
#include "Voyager/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

#include "Platform/APIType.h"

#include "Voyager/Core/Log.h"

namespace VE
{
	namespace Rendering 
	{
		VertexBuffer* VertexBuffer::create(float* vertices, std::uint32_t size, std::uint32_t count)
		{
			switch (Renderer::getAPI())
			{
			case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
			case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLVertexBuffer(vertices, size, count);
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}

		IndexBuffer* IndexBuffer::create(std::uint32_t* indices, std::uint32_t count)
		{
			switch (Renderer::getAPI())
			{
			case Platform::API::RenderAPI::None: VE_CORE_ASSERT(false, "RendererAPI::None is not supported");
			case Platform::API::RenderAPI::OpenGL: return new Platform::OpenGL::OpenGLIndexBuffer(indices, count);
			}

			VE_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
};