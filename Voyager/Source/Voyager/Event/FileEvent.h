#ifndef VE_FILE_EVENT_H
#define VE_FILE_EVENT_H

#include "Voyager/Event/Event.h"

#include <sstream>

namespace VE 
{
	namespace Event 
	{
		class VOYAGER_API FileEvent : public Event 
		{
		public:
			FileEvent(const std::string path) : _path(path) {}

			std::string getPath() const { return _path; }

			EVENT_CLASS_CATEGORY(VE_FILE);
		protected:
			std::string _path;
		};

		class VOYAGER_API FileCreatedEvent : public FileEvent 
		{
		public:
			FileCreatedEvent(const std::string path) : FileEvent(path) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "FileCreatedEvent: " << " (Path: " << _path.c_str() << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_FILE_CREATED)
			EVENT_CLASS_CATEGORY(VE_FILE)
		};

		class VOYAGER_API FileModifiedEvent : public FileEvent
		{
		public:
			FileModifiedEvent(const std::string path) : FileEvent(path) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "FileModifiedEvent: " << " (Path: " << _path.c_str() << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_FILE_MODIFIED)
			EVENT_CLASS_CATEGORY(VE_FILE)
		};

		class VOYAGER_API FileDeletedEvent : public FileEvent
		{
		public:
			FileDeletedEvent(std::string path) : FileEvent(path) {}

			std::string toString() const override
			{
				std::stringstream ss;
				ss << "FileDeletedEvent: " << " (Path: " << _path.c_str() << ")";
				return ss.str();
			}

			EVENT_CLASS_TYPE(VE_FILE_DELETED)
			EVENT_CLASS_CATEGORY(VE_FILE)
		};
	}
}

#endif