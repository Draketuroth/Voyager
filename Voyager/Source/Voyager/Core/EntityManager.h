#ifndef VE_ENTITY_MANAGER_H
#define VE_ENTITY_MANAGER_H

#include "Voyager/Core/IEntityManager.h"
#include "Voyager/Core/Types.h"
#include "Voyager/Core/Log.h"

#include <array>
#include <queue>

namespace VE 
{
	namespace Core 
	{
		class VOYAGER_API EntityManager : public IEntityManager
		{
		public:
			EntityManager() : _aliveEntitiesCount(0)
			{
				for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
				{
					_entities.push(entity);
				}
			}

			~EntityManager() {}

			Entity createEntity()
			{
				VE_CORE_ASSERT(_aliveEntitiesCount < MAX_ENTITIES, "Too many entities in existence!");

				Entity id = _entities.front();
				_entities.pop();
				++_aliveEntitiesCount;

				return id;
			}

			void destroyEntity(Entity entity)
			{
				VE_CORE_ASSERT(entity < MAX_ENTITIES, "Entity out of range!");
				_signatures[entity].reset();
				_entities.push(entity);
				--_aliveEntitiesCount;
			}

			void setSignature(Entity entity, Signature signature)
			{
				VE_CORE_ASSERT(entity < MAX_ENTITIES, "Entity out of range!");

				_signatures[entity] = signature;
			}

			Signature getSignature(Entity entity)
			{
				VE_CORE_ASSERT(entity < MAX_ENTITIES, "Entity out of range!");

				return _signatures[entity];
			}

		private:
			std::queue<Entity> _entities;
			std::array<Signature, MAX_ENTITIES> _signatures;
			std::uint32_t _aliveEntitiesCount;
		};
	}
}

#endif