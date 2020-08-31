
#include "Voyager/Renderer/Identifier.h"

namespace VE
{
	namespace Rendering
	{
		std::map<std::string, unsigned int>* Identifier::_stringTable = new std::map<std::string, unsigned int>;
	}
};