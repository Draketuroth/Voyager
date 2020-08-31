#ifndef VE_COMPONENT_EVENT_H
#define VE_COMPONENT_EVENT_H

#include <sstream>

#include "Voyager/Event/Event.h"
#include "Voyager/Core/Types.h"

namespace VE
{
	namespace Event
	{
		class VOYAGER_API ComponentEvent : public Event
		{
		public:
			ComponentEvent(Core::ComponentType componentType, Core::Entity entityId) : _componentType(componentType), _entityId(entityId) {}

			inline Core::Entity getEntityId() const { return _entityId; }
			inline Core::ComponentType getComponentType() const { return _componentType; }

			EVENT_CLASS_CATEGORY(VE_COMPONENT)
		protected:
			Core::ComponentType _componentType;
			Core::Entity _entityId;
		};

		class VOYAGER_API ComponentAddedEvent : public ComponentEvent
		{
		public:
			ComponentAddedEvent(Core::ComponentType componentType, Core::Entity entityId) : ComponentEvent(componentType, entityId) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "ComponentAddedEvent: " << " (Entity Id: " << _entityId << " Component Id: " << _componentType << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_COMPONENT_ADDED)
				EVENT_CLASS_CATEGORY(VE_COMPONENT)
		};

		class VOYAGER_API ComponentRemovedEvent : public ComponentEvent
		{
		public:
			ComponentRemovedEvent(Core::ComponentType componentType, Core::Entity entityId) : ComponentEvent(componentType, entityId) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "ComponentRemovedEvent: " << " (Entity Id: " << _entityId << " Component Id: " << _componentType << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_COMPONENT_REMOVED)
				EVENT_CLASS_CATEGORY(VE_COMPONENT)
		};
	}
}

#endif