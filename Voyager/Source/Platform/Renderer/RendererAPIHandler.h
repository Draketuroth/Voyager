#ifndef VE_PLATFORM_RENDERER_API_HANDLER_H
#define VE_PLATFORM_RENDERER_API_HANDLER_H

#include "Voyager/Core/Core.h"

#include "Platform/APIType.h"

namespace VE
{
	namespace Platform
	{
		namespace Renderer 
		{
			class VOYAGER_API RendererAPIHandler
			{
			public:
				inline static void setAPI(const Platform::API::RenderAPI renderApi) { api = renderApi; }
				inline static Platform::API::RenderAPI getAPI() { return api; }

			private:
				static Platform::API::RenderAPI api;
			};
		}
	}
};

#endif