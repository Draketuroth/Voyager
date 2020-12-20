#ifndef VE_RENDERER_API_H
#define VE_RENDERER_API_H

#include "Voyager/Renderer/RenderSettings.h"

#include "Voyager/Renderer/Geometry.h"
#include "Voyager/Math/Vector/Vector4.h"

#include "Platform/APIType.h"

namespace VE
{
	namespace Rendering 
	{
		class VOYAGER_API RendererAPIHandler
		{

		public:
			virtual void setViewport(std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height) = 0;
			virtual void setClearColor(float r, float g, float b, float a) = 0;
			virtual void setBackfaceCulling(bool enable) = 0;
			virtual void setDepthTest(bool enable) = 0;
			virtual void clear(unsigned int flags) = 0;

			virtual void draw(unsigned int numVertices) = 0;
			virtual void draw(Rendering::Geometry* geometry) = 0;

			inline static Platform::API::RenderAPI getAPI() { return api; }

		private:
			static Platform::API::RenderAPI api;
		};
	}
};

#endif