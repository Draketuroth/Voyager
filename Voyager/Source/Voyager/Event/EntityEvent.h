#ifndef VE_ENTITY_EVENT_H
#define VE_ENTITY_EVENT_H

#include <sstream>

#include "Voyager/Event/Event.h"
#include "Voyager/Core/Types.h"

namespace VE
{
	namespace Event
	{
		class VOYAGER_API EntityEvent : public Event 
		{
		public:
			EntityEvent(std::uint32_t id) : _id(id) {}

			inline Core::Entity getEntityId() const { return _id; }

			EVENT_CLASS_CATEGORY(VE_ENTITY)
		protected:
			Core::Entity _id;
		};

		class VOYAGER_API EntityCreatedEvent : public EntityEvent
		{
		public:
			EntityCreatedEvent(std::uint32_t id) : EntityEvent(id) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "EntityCreatedEvent: " << " (Id: " << _id << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_ENTITY_CREATED)
			EVENT_CLASS_CATEGORY(VE_ENTITY)
		};

		class VOYAGER_API EntityDestroyedEvent : public EntityEvent
		{
		public:
			EntityDestroyedEvent(std::uint32_t id) : EntityEvent(id) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "EntityDestroyedEvent: " << " (Id: " << _id << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_ENTITY_DESTROYED)
			EVENT_CLASS_CATEGORY(VE_ENTITY)
		};
	}
}

#endif