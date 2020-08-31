#ifndef VE_ISYSTEMMANAGER_H
#define VE_ISYSTEMMANAGER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Types.h"

namespace VE { namespace Core { class SystemManager;  } }

namespace VE
{
	namespace Core
	{
		class VOYAGER_API ISystemManager
		{
		public:
			virtual ~ISystemManager() = default;

			static SystemManager* create();
		};
	}
}

#endif
