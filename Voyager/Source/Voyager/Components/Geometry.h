#ifndef VE_COMPONENT_GEOMETRY_H
#define VE_COMPONENT_GEOMETRY_H

#include "Voyager/Core/Core.h"

#include "Voyager/Renderer/Geometry.h"

namespace VE
{
	namespace Components
	{
		struct Geometry
		{
			Geometry() { _geometry = nullptr; }

			void setGeometryResourcePointer(VE::Rendering::Geometry* geometryPtr)
			{
				_geometry = geometryPtr;
			}

			VE::Rendering::Geometry* getGeometry() 
			{
				return _geometry;
			}

			unsigned int getResourceHandle()
			{
				return _geometry->getHandle();
			}

			void setVertexBuffer(const VE::Core::Ref<VE::Rendering::VertexBuffer>& vertexBuffer) 
			{
				_geometry->setVertexBuffer(vertexBuffer);
			}
			void setIndexBuffer(const VE::Core::Ref<VE::Rendering::IndexBuffer>& indexBuffer) 
			{
				_geometry->setIndexBuffer(indexBuffer);
			}

		private:
			VE::Rendering::Geometry* _geometry;
		};
	}
}

#endif