#ifndef VE_SHADERSET_H
#define VE_SHADERSET_H

#include "Voyager/Renderer/Shader.h"
#include <vector>

namespace VE 
{
	namespace Rendering 
	{
		class VOYAGER_API ShaderSet
		{
		public:
			virtual ~ShaderSet() = default;

			static ShaderSet* create(std::vector<Rendering::Shader*> shaders);
		};
	}
}

#endif