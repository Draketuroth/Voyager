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

namespace Graphics
{
#ifdef OPENGL_ACTIVE_RENDERER

	struct Geometry
	{
		Geometry() : vertices(nullptr), num_vertices(0), indices(nullptr), num_indices(0) {}

		Vertex* vertices;
		GLuint num_vertices;
		GLushort* indices;
		GLuint num_indices;

		GLsizeiptr vertexBufferSize() const { return num_vertices * sizeof(Vertex); }
		GLsizeiptr indexBufferSize() const { return num_indices * sizeof(GLushort); }
		void release() 
		{ 
		delete[] vertices; 
		delete[] indices; 
		num_vertices = 0; 
		}

	};
#endif
}

#endif
