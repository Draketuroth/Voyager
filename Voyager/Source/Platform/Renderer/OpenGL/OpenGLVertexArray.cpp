
#include "Platform/Renderer/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			static GLenum shaderDataTypeToOpenGLBaseType(Rendering::ShaderDataType type)
			{
				switch (type)
				{
				case VE::Rendering::ShaderDataType::Float:    return GL_FLOAT;
				case VE::Rendering::ShaderDataType::Float2:   return GL_FLOAT;
				case VE::Rendering::ShaderDataType::Float3:   return GL_FLOAT;
				case VE::Rendering::ShaderDataType::Float4:   return GL_FLOAT;
				case VE::Rendering::ShaderDataType::Mat3:     return GL_FLOAT;
				case VE::Rendering::ShaderDataType::Mat4:     return GL_FLOAT;
				case VE::Rendering::ShaderDataType::Int:      return GL_INT;
				case VE::Rendering::ShaderDataType::Int2:     return GL_INT;
				case VE::Rendering::ShaderDataType::Int3:     return GL_INT;
				case VE::Rendering::ShaderDataType::Int4:     return GL_INT;
				case VE::Rendering::ShaderDataType::Bool:     return GL_BOOL;
				}

				VE_CORE_ASSERT(false, "Unknown ShaderDataType!");
				return 0;
			}

			OpenGLVertexArray::OpenGLVertexArray()
			{
				glCreateVertexArrays(1, &_arrayID);
			}
			OpenGLVertexArray::~OpenGLVertexArray()
			{
				glDeleteVertexArrays(1, &_arrayID);
			}
			void OpenGLVertexArray::bind() const
			{
				glBindVertexArray(_arrayID);
			}
			void OpenGLVertexArray::unbind() const
			{
				glBindVertexArray(0);
			}
			void OpenGLVertexArray::setVertexBuffer(const VE::Core::Ref<Rendering::VertexBuffer>& vertexBuffer)
			{
				VE_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");

				glBindVertexArray(_arrayID);
				vertexBuffer->bind();

				uint32_t index = 0;
				const auto& layout = vertexBuffer->getLayout();
				for (const auto& element : layout)
				{
					glEnableVertexAttribArray(index);
					glVertexAttribPointer(index,
						element.getComponentCount(),
						shaderDataTypeToOpenGLBaseType(element._type),
						element._normalized ? GL_TRUE : GL_FALSE,
						layout.getStride(),
						(const void*)element._offset);
					index++;
				}

				_vertexBuffer = vertexBuffer;
			}
			void OpenGLVertexArray::setIndexBuffer(const VE::Core::Ref<Rendering::IndexBuffer>& indexBuffer)
			{
				glBindVertexArray(_arrayID);
				indexBuffer->bind();

				_indexBuffer = indexBuffer;

				_indexed = true;
			}
			bool OpenGLVertexArray::isIndexed() const
			{
				return _indexed;
			}
		}
	}
};