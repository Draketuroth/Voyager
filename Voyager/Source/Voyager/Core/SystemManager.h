#ifndef VE_SYSTEM_MANAGER_H
#define VE_SYSTEM_MANAGER_H

#include "Voyager/Core/Core.h"
#include "Voyager/Core/Types.h"
#include "Voyager/Core/System.h"

#include "Voyager/Core/Log.h"

#include "Voyager/Core/ISystemManager.h"

#include <memory>
#include <unordered_map>

namespace VE 
{
	namespace Core 
	{
		class VOYAGER_API SystemManager : public ISystemManager
		{
		public:
			virtual ~SystemManager() {}

			template<typename T>
			VE::Core::Ref<T> registerSystem() 
			{
				const char* typeName = typeid(T).name();

				VE_CORE_ASSERT(_systems.find(typeName) == _systems.end(), "Registering system more than once.");

				// Create a pointer to the system and return it so it can be used externally.
				auto system = std::make_shared<T>();
				_systems.insert(std::make_pair(typeName, system));
				return system;
			}

			template<typename T>
			void setSignature(Signature signature) 
			{
				const char* typeName = typeid(T).name();

				VE_CORE_ASSERT(_systems.find(typeName) != _systems.end(), "System used before registered.");

				// Set the signature for this system.
				_signatures.insert(std::make_pair(typeName, signature));
			}

			void entityDestroyed(Entity entity) 
			{
				for (auto const& pair : _systems) 
				{
					auto const& system = pair.second;
					system->_entities.erase(entity);
				}
			}

			void entitySignatureChanged(Entity entity, Signature entitySignature) 
			{
				// Notify each system that an entity's signature changed.
				for (auto const& pair : _systems) 
				{
					auto const& type = pair.first;
					auto const& system = pair.second;
					auto const& systemSignature = _signatures[type];

					// Entity signature matches system signature - insert into set.
					if ((entitySignature & systemSignature) == systemSignature) 
					{
						system->_entities.insert(entity);
					}
					// Entity signature does not match system signature - erase from set.
					else
					{
						system->_entities.erase(entity);
					}
				}
			}

		private:
			// Map from system type string pointer to a signature.
			std::unordered_map<const char*, Signature> _signatures{};

			// Map from system type string pointer to a system pointer.
			std::unordered_map<const char*, VE::Core::Ref<System>> _systems{};
		};
	}
}

#endif