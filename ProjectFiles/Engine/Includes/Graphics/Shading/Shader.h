#ifndef VE_GRAPHICS_SHADER_H
#define VE_GRAPHICS_SHADER_H

#include <string>

#if defined DLL_EXPORT_GRAPHICS
#define DECLDIR_R __declspec(dllexport)
#else
#define DECLDIR_R __declspec(dllimport)
#endif

namespace Graphics
{
	class DECLDIR_R Shader
	{
	public:

		Shader();
		~Shader();

		std::string readShaderCode(const char* file_name);
	};
}
#endif
