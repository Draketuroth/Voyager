//============================================================================
// # VOYAGER ENGINE #
// Name: Renderable.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: Class for managing renderables.
//============================================================================

#ifndef VE_GRAPHICS_RENDERABLE_H
#define VE_GRAPHICS_RENDERABLE_H

#include <gl/glew.h>
#include <glm.hpp>

#include <Graphics/Rendering/Geometry.h>

namespace Graphics
{
	class Renderable
	{
		friend class GLRenderer;
	public:
		Renderable();
		~Renderable();

		glm::mat4 transform;
	private:

		GLuint _geometry_index_byte_offset;
		GLuint _normal_index_byte_offset;

		GLuint _geometry_buffer_ID;
		GLuint _normal_buffer_ID;

		Geometry _geometry;
		GLuint _geometry_vao_ID;

		Geometry _normal;
		GLuint _normal_vao_ID;
	};
}

#endif

