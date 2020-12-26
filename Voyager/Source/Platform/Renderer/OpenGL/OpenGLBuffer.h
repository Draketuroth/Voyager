#ifndef VE_OPENGL_BUFFER_H
#define VE_OPENGL_BUFFER_H

#include "Voyager/Renderer/Buffer.h"
#include <glad/glad.h>

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLVertexBuffer : public Rendering::VertexBuffer
			{
			public:
				OpenGLVertexBuffer(float* vertices, std::uint32_t size, std::uint32_t count);
				virtual ~OpenGLVertexBuffer();

				virtual void bind() const override;
				virtual void unbind() const override;

				virtual std::uint32_t getCount() const { return _count; };

				virtual const Rendering::BufferLayout& getLayout() const override { return _layout; }
				virtual void setLayout(const Rendering::BufferLayout& layout) override { _layout = layout; }

			private:
				GLuint _bufferID;
				std::uint32_t _count;
				Rendering::BufferLayout _layout;
			};

			class OpenGLIndexBuffer : public Rendering::IndexBuffer
			{
			public:
				OpenGLIndexBuffer(uint32_t* indices, std::uint32_t count);
				virtual ~OpenGLIndexBuffer();

				virtual void bind() const;
				virtual void unbind() const;

				virtual std::uint32_t getCount() const { return _count; };

			private:
				GLuint _bufferID;
				std::uint32_t _count;
			};
		}
	}
};

#endif