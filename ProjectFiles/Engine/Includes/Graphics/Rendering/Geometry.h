//============================================================================
// # VOYAGER ENGINE #
// Name: Geometry.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 31, 2018
// Description: Custom datatype for storing shape data
//============================================================================

#ifndef VE_GRAPHICS_GEOMETRY_H
#define VE_GRAPHICS_GEOMETRY_H

#include <gl/glew.h>
#include <Graphics/Primitives/Vertex.h>
#include <Core/Misc/TypeDefs.h>

namespace Graphics
{
	struct Geometry
	{
		Geometry() : vertices(nullptr), num_vertices(0), indices(nullptr), num_indices(0) {}

		Vertex* vertices;
		GLuint num_vertices;
		ushort* indices;
		GLuint num_indices;
		GLenum render_mode;

		GLsizeiptr vertexBufferSize() const { return num_vertices * sizeof(Vertex); }
		GLsizeiptr indexBufferSize() const { return num_indices * sizeof(ushort); }
		void release() 
		{ 
		delete[] vertices; 
		delete[] indices; 
		num_vertices = 0; 
		}

	};
}

#endif
