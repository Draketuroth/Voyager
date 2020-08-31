#ifndef VE_SYSTEM_H
#define VE_SYSTEM_H

#include "Voyager/Core/Types.h"
#include <set>


namespace VE 
{
	namespace Core 
	{
		class System
		{
		public:
			std::set<Entity> _entities;
		};
	}
}

#endif
