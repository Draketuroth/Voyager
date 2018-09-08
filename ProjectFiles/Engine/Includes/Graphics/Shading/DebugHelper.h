//============================================================================
// # VOYAGER ENGINE #
// Name: DebugHelper.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: OpenGL error checking functions.
//============================================================================

#ifndef VE_GRAPHICS_DEBUGHELPER_H
#define VE_GRAPHICS_DEBUGHELPER_H

#include <gl/glew.h>

namespace Graphics
{
	bool checkStatus(
		GLuint object_id,
		PFNGLGETSHADERIVPROC object_property_getter,
		PFNGLGETSHADERINFOLOGPROC info_log_func,
		GLenum status_type);
}

#endif
