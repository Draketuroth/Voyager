
#include "Voyager/Renderer/Identifier.h"

namespace VE
{
	namespace Rendering
	{
		VE::Core::Scope<std::map<std::string, unsigned int>> Identifier::_stringTable(new std::map<std::string, unsigned int>);
	}
};