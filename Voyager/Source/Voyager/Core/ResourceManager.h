#ifndef VE_RESOURCEMANAGER_H
#define VE_RESOURCEMANAGER_H

#include <vector>
#include <stack>
#include <string>
#include <functional>

#include "Voyager/Core/Log.h"
#include "Voyager/IO/ImportSettings.h"

#define SAFE_DELETE( p )       { if( p ) { delete ( p );     ( p ) = NULL; } }

namespace VE 
{
	namespace Core 
	{
		template<class T>
		class ResourceManager 
		{
		public:
			using ResourceCreateCallbackFn = std::function<void(T** resource, const std::string path, VE::IO::Setting& flags)>;

			ResourceManager() {};

			ResourceManager(ResourceCreateCallbackFn&& CreateResourceFunction)
			{
				_list = new std::vector<T*>;

				CreateResource = CreateResourceFunction;
			}

			~ResourceManager()
			{
				emptyList();
				delete _list;
			}

			std::vector<T*> getList() 
			{
				return _list;
			}

			T* getElement(const std::string& name, const std::string path = "./") 
			{
				// Ensure name and path are valid, and that the list is valid and not empty
				if (name.empty() || path.empty() || _list == NULL || _list->empty()) 
				{
					return NULL;
				}

				// Iterate the list looking for the specified resource
				for (std::vector<T*>::iterator i = _list->begin(); i != _list->end(); i++) 
				{
					if ((*i) != NULL) 
					{
						if ((*i)->getName() == name)
						{
							if ((*i)->getPath() == path)
							{
								return (*i);
							}
						}
					}
				}

				// Return NULL if the resource was not found
				return NULL;
			}

			T* getElement(const int handle) 
			{
				if (handle < _list->size() && handle >= 0) 
				{
					return (*_list)[handle];
				}

			}

			void emptyList() 
			{
				for (std::vector<T*>::iterator i = _list->begin(); i != _list->end(); i++) 
				{
					SAFE_DELETE(*i);
				}

				while (!_handles.empty()) 
				{
					_handles.pop();
				}

				_list->clear();
				_list->swap(*_list);
			}

			void remove(const unsigned int handle) 
			{
				if (handle < 0 || _list == NULL || handle >= _list->size() || (*_list)[handle] == NULL) 
				{
					return;
				}

				T* resource = (*_list)[handle];

				// Decrement the resource reference count
				resource->decreaseReference();

				// If the resource is no longer used, then destroy it
				if (resource->getReferenceCount() == 0) 
				{
					// Add the handle to the stack of free handles
					_handles.push(handle);

					// Delete the resource
					delete resource;

					// Mark the slot as NULL
					(*_list)[handle] = NULL;
				}
			}

			unsigned int add(const std::string& name, const std::string& path = "./", VE::IO::Setting flags = VE::IO::None) 
			{
				if (CreateResource != NULL)
				{
					// Ensure the list, the resource name, and its path are valid
					if (_list == NULL || name.empty() || path.empty())
					{
						return -1;
					}

					// If the element already exists, then return a pointer to it
					T* element = getElement(name, path);
					if (element != NULL)
					{
						element->increaseReference();
						return element->getHandle();
					}

					// Check if there is an available handle. If not, use a new handle
					bool handleAvailable = !_handles.empty();
					unsigned int handle;
					if (handleAvailable)
					{
						handle = _handles.top();
						_handles.pop();
					}
					else
					{
						handle = _list->size();
					}

					// Create the resource through the application specific function.
					T* resource = NULL;
					CreateResource(&resource, path, flags);

					resource->setName(name);
					resource->setPath(path);

					// Add the resource to the manager. If there is an available handle, then the resource is stored
					// using the handle. Otherwise the resource is added to the vector
					if (handleAvailable)
					{
						(*_list)[handle] = resource;
					}
					else
					{
						_list->push_back(resource);
					}

					//return the handle
					return handle;
				}
				VE_CORE_WARN("Failed to add resource with name {0} and path {1}\nCreate function not provided!", name.c_str(), path.c_str());
				return -1;
			}

			T* operator [](unsigned int handle) 
			{
				if (handle < _list->size() && handle >= 0) 
				{
					return (*_list)[handle];
				}

				return NULL;
			}

		private:

			std::stack<unsigned int> _handles;
			std::vector<T*>* _list; // List of pointers to resources.
			ResourceCreateCallbackFn CreateResource; // Application specific resource creation.

		};
	}
}


#endif