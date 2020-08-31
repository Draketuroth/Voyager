
#include "Voyager/Core/ISystemManager.h"
#include "Voyager/Core/SystemManager.h"

namespace VE
{
	namespace Core
	{
		SystemManager* ISystemManager::create()
		{
			return new SystemManager();
		}
	}
}