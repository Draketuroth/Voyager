
#include "Voyager/Renderer/Renderer.h"
#include "Voyager/Renderer/Material.h"

#include "Voyager/Renderer/Material/Standard.h"

namespace VE
{
	namespace Rendering
	{
		void Material::createResource(Material** resource, const std::string path, VE::IO::Setting flags)
		{
			*resource = new StandardMaterial();
		}
		Material* Material::create()
		{
			return new StandardMaterial();
		}
	}
}