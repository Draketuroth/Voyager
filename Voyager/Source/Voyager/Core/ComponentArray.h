#ifndef VE_COMPONENT_ARRAY_H
#define VE_COMPONENT_ARRAY_H

#include "Voyager/Core/Types.h"
#include "Voyager/Core/Log.h"
#include "Voyager/Event/Event.h"

#include <array>
#include <unordered_map>

namespace VE
{
	namespace Core
	{
		class IComponentArray 
		{
		public:
			virtual ~IComponentArray() = default;
			virtual void entityDestroyed(Entity entity) = 0;
		};

		template <typename T>
		class ComponentArray : public IComponentArray 
		{
		public:
			void insertData(Entity entity, T component) 
			{
				VE_CORE_ASSERT(_entityToIndexMap.find(entity) == _entityToIndexMap.end(), "Component added to same entity more than once.");

				// Put new entry at end and update the maps.
				size_t newIndex = _size;
				_entityToIndexMap[entity] = newIndex;
				_indexToEntityMap[newIndex] = entity;
				_componentArray[newIndex] = component;
				_size++;
			}
			void removeData(Entity entity) 
			{
				VE_CORE_ASSERT(_entityToIndexMap.find(entity) != _entityToIndexMap.end(), "Removing non-existing component.");

				// Copy element at end into deleted element's place to maintain density
				size_t indexOfRemovedEntity = _entityToIndexMap[entity];
				size_t indexOfLastElement = _size - 1;
				_componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

				// Update map to point to moved spot.
				Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
				_entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
				_indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

				_entityToIndexMap.erase(entity);
				_indexToEntityMap.erase(indexOfLastElement);

				--_size;
			}
			T& getData(Entity entity) 
			{
				VE_CORE_ASSERT(_entityToIndexMap.find(entity) != _entityToIndexMap.end(), "Retrieving non-existing component.");

				// Return a reference to the entity's component.
				return _componentArray[_entityToIndexMap[entity]];
			}

			void entityDestroyed(Entity entity) override 
			{
				if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) 
				{
					// Remove the entity's component if it existed.
					removeData(entity);
				}
			}

		private:

			std::array<T, MAX_ENTITIES> _componentArray;

			// The unordered maps does have a performance penalty since when we want the ID of a component
			// to grab it from the contigous array, we have to request it from the unordered map which is
			// contigous. 
			std::unordered_map<Entity, size_t> _entityToIndexMap;

			std::unordered_map<size_t, Entity> _indexToEntityMap;

			size_t _size;
		};
	}
}

#endif