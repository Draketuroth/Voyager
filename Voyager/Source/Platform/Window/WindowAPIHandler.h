#ifndef VE_WINDOW_API_H
#define VE_WINDOW_API_H

#include "Voyager/Core/Core.h"

#include "Platform/APIType.h"

namespace VE
{
	namespace Platform
	{
		namespace Window 
		{
			class VOYAGER_API WindowAPIHandler
			{

			public:
				inline static API::WindowAPI getAPI() { return api; }

			private:
				static API::WindowAPI api;
			};
		}
	}
};

#endif