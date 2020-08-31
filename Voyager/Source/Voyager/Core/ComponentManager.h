#ifndef VE_COMPONENT_MANAGER_H
#define VE_COMPONENT_MANAGER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/ComponentArray.h"

#include "Voyager/Core/IComponentManager.h"

#include <unordered_map>

namespace VE
{
	namespace Core
	{
		class VOYAGER_API ComponentManager : public IComponentManager
		{
		public:
			virtual ~ComponentManager() {}

			template<typename T>
			void registerComponent() 
			{
				const char* typeName = typeid(T).name();

				VE_CORE_ASSERT(_componentTypes.find(typeName) == _componentTypes.end(), "Registering component type more than once.");

				// Add this component type to the component type map.
				_componentTypes.insert(std::make_pair(typeName, _nextComponentType));

				// Create component array pointer and add it to the component arrays map.
				_componentArrays.insert(std::make_pair(typeName, std::make_shared<ComponentArray<T>>()));

				// Increment the value so that the next component registered will be different.
				_nextComponentType++;

			}

			template<typename T>
			ComponentType getComponentType() 
			{
				const char* typeName = typeid(T).name();

				VE_CORE_ASSERT(_componentTypes.find(typeName) != _componentTypes.end(), "Component not registered before use!");

				// Return this component's type - used for creating signatures.
				return _componentTypes[typeName];
			}

			template<typename T>
			void addComponent(Entity entity, T component)
			{
				// Add a component to the array for an entity.
				getComponentArray<T>()->insertData(entity, component);
			}

			template<typename T>
			void removeComponent(Entity entity)
			{
				// Remove a component to the array for an entity.
				getComponentArray<T>()->removeData(entity);
			}

			template<typename T>
			T& getComponent(Entity entity)
			{
				return getComponentArray<T>()->getData(entity);
			}

			void entityDestroyed(Entity entity) 
			{
				// Notify each component array that an entity has been destroyed. 
				// If it has a component for that entity, it will remove it.

				// TODO: Make event driven instead!
				for (auto const& pair : _componentArrays) 
				{
					auto const& component = pair.second;

					component->entityDestroyed(entity);
				}
			}

		private:

			// Map from type string pointer to a component type.
			std::unordered_map<const char*, ComponentType> _componentTypes{};

			// Map from type string pointer to a component array.
			std::unordered_map<const char*, VE::Core::Ref<IComponentArray>> _componentArrays{};

			// The component type to be assigned to the net registered component - starting at 0.
			ComponentType _nextComponentType{};

			template <typename T>
			VE::Core::Ref<ComponentArray<T>> getComponentArray() 
			{
				const char* typeName = typeid(T).name();

				VE_CORE_ASSERT(_componentTypes.find(typeName) != _componentTypes.end(), "Component not registered before use!");

				return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
			}
		};
	}
}

#endif