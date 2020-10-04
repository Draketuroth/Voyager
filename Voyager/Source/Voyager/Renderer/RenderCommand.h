#ifndef VE_RENDER_COMMAND_H
#define VE_RENDER_COMMAND_H

#include "Voyager/Renderer/RendererAPI.h"
#include "Voyager/Renderer/RenderFlags.h"

#include "Voyager/Core/Bitmask.h"

namespace VE
{
	namespace Rendering 
	{
		class VOYAGER_API RenderCommand
		{
		public:
			inline static void setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height)
			{
				_renderAPI->setViewport(x, y, width, height);
			}

			inline static void setClearColor(float r, float g, float b, float a)
			{
				_renderAPI->setClearColor(r, g, b, a);
			}

			inline static void setBackfaceCulling(bool enabled) 
			{
				_renderAPI->setBackfaceCulling(enabled);
			}

			inline static void setDepthTest(bool enabled)
			{
				_renderAPI->setDepthTest(enabled);
			}

			inline static void clear(Core::Bitmask<ClearFlags> clearFlags)
			{
				unsigned int flags = 0x00000000;

				// TODO: Improve api checking and eliminate magic bit values.
				RendererAPI::API api = _renderAPI->GetAPI();
				if (api == RendererAPI::API::OpenGL) 
				{
					if (clearFlags & ClearFlags::COLOR)
					{
						flags |= 0x00004000;
					}
					if (clearFlags & ClearFlags::DEPTH)
					{
						flags |= 0x00000100;
					}
				}
				else 
				{
					return;
				}

				_renderAPI->clear(flags);
			}

			inline static void draw(unsigned int numVertices) 
			{
				_renderAPI->draw(numVertices);
			}

			inline static void draw(Rendering::Geometry* geometry)
			{
				_renderAPI->draw(geometry);
			}

		private:
			static RendererAPI* _renderAPI;
		};
	}
};

#endif