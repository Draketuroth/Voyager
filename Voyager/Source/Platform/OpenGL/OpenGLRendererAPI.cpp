
#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include "Platform/OpenGL/OpenGLStatus.h"

#include <glad/glad.h>

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			void OpenGLRendererAPI::setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height)
			{
				glViewport(x, y, width, height);
				_width = width;
				_height = height;
			}
			void OpenGLRendererAPI::setClearColor(float r, float g, float b, float a)
			{
				glClearColor(r, g, b, a);
			}
			void OpenGLRendererAPI::setBackfaceCulling(bool enabled)
			{
				if (enabled) 
				{
					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);
				}
				else 
				{
					glDisable(GL_CULL_FACE);
				}
				
			}
			void OpenGLRendererAPI::setDepthTest(bool enabled)
			{
				if (enabled)
				{
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_LESS);
				}
				else
				{
					glDisable(GL_DEPTH_TEST);
				}
			}
			void OpenGLRendererAPI::clear()
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}
			void OpenGLRendererAPI::draw(unsigned int numVertices)
			{
				if (emptyVAO == false) 
				{
					glCreateVertexArrays(1, &_bgVao);
					emptyVAO == true;
				}
				glBindVertexArray(_bgVao);
				glDrawArrays(GL_TRIANGLES, 0, numVertices);
			}
			void OpenGLRendererAPI::draw(Rendering::Geometry* geometry)
			{
				if (geometry) 
				{
					static_cast<OpenGLVertexArray*>(geometry)->bind();
					geometry->isIndexed() ? glDrawElements(GL_TRIANGLES, geometry->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr) : 
											glDrawArrays(GL_TRIANGLES, 0, geometry->getVertexBuffer()->getCount());
				}
			}
		}
	}
};