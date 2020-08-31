#ifndef VE_RESOURCE_H
#define VE_RESOURCE_H

#include <string>

#include "Voyager/Core/Core.h"

namespace VE 
{
	namespace Core 
	{
		class VOYAGER_API Resource 
		{
		public:
			virtual ~Resource() = default;

			// Override these for specific resource handling in derived classes, if needed.

			virtual std::string getName() const { return _name; }
			virtual std::string getFilename() const { return _filename; }
			virtual std::string getPath() const { return _path; }

			virtual void setName(const std::string name) { _name = name; }
			virtual void setFilename(const std::string filename) { _filename = filename; }
			virtual void setPath(const std::string path) { _path = path; }

			virtual unsigned int getHandle() const { return _handle; }
			virtual unsigned long getReferenceCount() const { return _refCount; }

			virtual void increaseReference() { _refCount++; }
			virtual void decreaseReference() { _refCount--; }

		protected:
			std::string _name;
			std::string _filename;
			std::string _path;

			unsigned int _handle;
			unsigned long _refCount;

		};
	}
}


#endif