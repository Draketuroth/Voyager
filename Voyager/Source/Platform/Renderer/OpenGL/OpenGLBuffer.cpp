
#include "Platform/Renderer/OpenGL/OpenGLBuffer.h"

namespace VE
{
	namespace Platform
	{
		namespace OpenGL 
		{
			// Vertex Buffer ///////////////////////////////////////////////////////////////

			OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, std::uint32_t size, std::uint32_t count) : _count(count)
			{
				glCreateBuffers(1, &_bufferID);
				glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
				glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
			}

			OpenGLVertexBuffer::~OpenGLVertexBuffer()
			{
				glDeleteBuffers(1, &_bufferID);
			}

			void OpenGLVertexBuffer::bind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, _bufferID);
			}
			void OpenGLVertexBuffer::unbind() const
			{
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}

			// Index Buffer ///////////////////////////////////////////////////////////////

			OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, std::uint32_t count) : _count(count)
			{
				glCreateBuffers(1, &_bufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(std::uint32_t), indices, GL_STATIC_DRAW);
			}
			OpenGLIndexBuffer::~OpenGLIndexBuffer()
			{
				glDeleteBuffers(1, &_bufferID);
			}
			void OpenGLIndexBuffer::bind() const
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _bufferID);
			}
			void OpenGLIndexBuffer::unbind() const
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			}
		}
	}
};