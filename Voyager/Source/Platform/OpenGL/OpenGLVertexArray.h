#ifndef VE_OPENGL_VERTEX_ARRAY_H
#define VE_OPENGL_VERTEX_ARRAY_H

#include "Voyager/Renderer/Geometry.h"

namespace VE
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLVertexArray : public Rendering::Geometry
			{
			public:
				OpenGLVertexArray();
				virtual ~OpenGLVertexArray();

				virtual void bind() const;
				virtual void unbind() const;

				virtual void setVertexBuffer(const VE::Core::Ref<Rendering::VertexBuffer>& vertexBuffer) override;
				virtual void setIndexBuffer(const VE::Core::Ref<Rendering::IndexBuffer>& indexBuffer) override;

				virtual bool isIndexed() const override;

				virtual const VE::Core::Ref<Rendering::VertexBuffer>& getVertexBuffer() const { return _vertexBuffer; }
				virtual const VE::Core::Ref<Rendering::IndexBuffer>& getIndexBuffer() const { return _indexBuffer; }

			private:
				std::uint32_t _arrayID;
				bool _indexed = false;

				VE::Core::Ref<Rendering::VertexBuffer> _vertexBuffer;
				VE::Core::Ref<Rendering::IndexBuffer> _indexBuffer;
			};
		}
	}
};

#endif