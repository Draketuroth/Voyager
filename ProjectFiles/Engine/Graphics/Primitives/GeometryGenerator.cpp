//============================================================================
// # VOYAGER ENGINE #
// Name: GeometryGenerator.cpp
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 31, 2018
// Description: Geometry factory class
//============================================================================

#include <Graphics/Primitives/GeometryGenerator.h>
#include <glm.hpp>
#include <Graphics/Primitives/Vertex.h>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);

namespace Graphics
{
	Geometry ret;
	Geometry GeometryGenerator::makeTriangle()
	{
		Vertex verts[] =
		{
			glm::vec3(+0.0f, +1.0f, +0.0f),
			glm::vec3(+1.0f, +0.0f, +0.0f),

			glm::vec3(-1.0f, -1.0f, +0.0f),
			glm::vec3(+0.0f, +1.0f, +0.0f),

			glm::vec3(+1.0f, -1.0f, +0.0f),
			glm::vec3(+0.0f, +0.0f, +1.0f),
		};
		ret.num_vertices = NUM_ARRAY_ELEMENTS(verts);
		ret.vertices = new Vertex[ret.num_vertices];
		memcpy(ret.vertices, verts, sizeof(verts));

		GLushort indices[] = { 0, 1, 2 };
		ret.num_indices = NUM_ARRAY_ELEMENTS(indices);
		ret.indices = new GLushort[ret.num_indices];
		memcpy(ret.indices, indices, sizeof(indices));

		return ret;
	}
}