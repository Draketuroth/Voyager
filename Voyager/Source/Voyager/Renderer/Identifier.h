#ifndef VE_RENDERING_IDENTIFIER_H
#define VE_RENDERING_IDENTIFIER_H

#include <map>
#include <string>
#include "Voyager/Core/Core.h"

namespace VE 
{
	namespace Rendering 
	{
		class VOYAGER_API Identifier 
		{
		public:
			enum class IdentifierType : unsigned int
			{
				PIPELINE,
				BUFFER,
				SHADERSET,
				RENDERTARGET
			};

			inline static unsigned int get(const std::string identifier, IdentifierType type)
			{
				unsigned int handle = -1;

				std::string id = identifier;
				id.append(std::to_string(static_cast<unsigned int>(type)));

				auto stringIdentifier = _stringTable->find(id);
				if (stringIdentifier != _stringTable->end())
				{
					return stringIdentifier->second;
				}
				else 
				{
					handle = _stringTable->size();
					_stringTable->insert(std::make_pair(id, handle));
					
				}
				return handle;
			}

		private:
			static std::map<std::string, unsigned int>* _stringTable;
		};
	}
}

#endif