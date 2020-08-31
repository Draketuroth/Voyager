
#include "Voyager/Core/IEntityManager.h"
#include "Voyager/Core/EntityManager.h"

namespace VE 
{
	namespace Core 
	{
		EntityManager* IEntityManager::create()
		{
			return new EntityManager();
		}
	}
}