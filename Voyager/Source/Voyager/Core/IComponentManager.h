#ifndef VE_ICOMPONENTMANAGER_H
#define VE_ICOMPONENTMANAGER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Types.h"

namespace VE { namespace Core { class ComponentManager;  } }

namespace VE
{
	namespace Core
	{
		class VOYAGER_API IComponentManager
		{
		public:
			virtual ~IComponentManager() = default;

			static ComponentManager* create();
		};
	}
}

#endif
