#ifndef VE_OPENGL_RENDERER_API_H
#define VE_OPENGL_RENDERER_API_H

#include "Voyager/Renderer/RendererAPIHandler.h"

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLRendererAPI : public Rendering::RendererAPIHandler
			{
			public:
				virtual void setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) override;
				virtual void setClearColor(float r, float g, float b, float a) override;
				virtual void setBackfaceCulling(bool enabled) override;
				virtual void setDepthTest(bool enabled) override;
				virtual void clear(unsigned int flags) override;

				virtual void draw(unsigned int numVertices) override;
				virtual void draw(Rendering::Geometry* geometry) override;

			private:
				bool emptyVAO = false;

				unsigned int _width = 0;
				unsigned int _height = 0;
				unsigned int _bgProgram;
				unsigned int _bgVao;
			};
		}
	}
};

#endif