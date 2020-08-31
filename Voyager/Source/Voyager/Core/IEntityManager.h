#ifndef VE_IENTITYMANAGER_H
#define VE_IENTITYMANAGER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Types.h"

namespace VE { namespace Core { class EntityManager; } }

namespace VE
{
	namespace Core
	{
		class VOYAGER_API IEntityManager
		{
		public:
			virtual ~IEntityManager() = default;

			static EntityManager* create();
		};
	}
}

#endif