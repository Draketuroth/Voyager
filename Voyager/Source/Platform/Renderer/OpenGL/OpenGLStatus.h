#ifndef VE_OPENGL_STATUS_H
#define VE_OPENGL_STATUS_H

#include <glad/glad.h>
#include <iostream>

namespace VE 
{
	namespace Platform 
	{
		namespace OpenGL 
		{
			class OpenGLStatus
			{
			public:
				static bool status(GLuint object_id, PFNGLGETSHADERIVPROC object_property_getter, PFNGLGETSHADERINFOLOGPROC info_log_func, GLenum status_type);
			};
		}
	}
}

#endif
