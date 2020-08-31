
#include "Voyager/Core/IComponentManager.h"
#include "Voyager/Core/ComponentManager.h"

namespace VE
{
	namespace Core
	{
		ComponentManager* IComponentManager::create()
		{
			return new ComponentManager();
		}
	}
}