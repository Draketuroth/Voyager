#ifndef VE_GEOMETRY_H
#define VE_GEOMETRY_H

#include <memory>
#include "Voyager/Renderer/Buffer.h"

#include "Voyager/Core/Resource.h"
#include "Voyager/IO/ImportSettings.h"

namespace VE
{
	namespace Rendering 
	{
		class VOYAGER_API Geometry : public Core::Resource
		{
		public:
			virtual ~Geometry() {}

			virtual void setVertexBuffer(const VE::Core::Ref<VertexBuffer>& vertexBuffer) = 0;
			virtual void setIndexBuffer(const VE::Core::Ref<IndexBuffer>& indexBuffer) = 0;

			// virtual const std::vector<VE::Core::Ref<VertexBuffer>>& getVertexBuffer() const = 0;
			virtual const VE::Core::Ref<VertexBuffer>& getVertexBuffer() const = 0;
			virtual const VE::Core::Ref<IndexBuffer>& getIndexBuffer() const = 0;

			virtual bool isIndexed() const = 0;

			static void createResource(Geometry** resource, const std::string path, VE::IO::Setting flags);
			static Geometry* create();
		};
	}
};

#endif