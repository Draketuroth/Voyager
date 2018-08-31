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
using namespace glm;

namespace Graphics
{
	Geometry GeometryGenerator::makeTriangle()
	{
		Geometry ret;
		Vertex verts[] =
		{
			vec3(+0.0f, +1.0f, +0.0f),
			vec3(+1.0f, +0.0f, +0.0f),

			vec3(-1.0f, -1.0f, +0.0f),
			vec3(+0.0f, +1.0f, +0.0f),

			vec3(+1.0f, -1.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),
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

	Geometry GeometryGenerator::makeCube()
	{
		Geometry ret;
		Vertex cube_verts[] =
		{
			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+1.0f, +0.0f, +0.0f),
			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+1.0f, +1.0f, +1.0f),

			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+1.0f, +0.0f, +1.0f),
			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +0.5f, +0.2f),
			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.8f, +0.6f, +0.4f),
			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.3f, +1.0f, +0.5f),

			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.2f, +0.5f, +0.2f),
			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.9f, +0.3f, +0.7f),
			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.3f, +0.7f, +0.5f),
			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.5f, +0.7f, +0.5f),

			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+0.7f, +0.8f, +0.2f),
			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+0.5f, +0.7f, +0.3f),
			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.4f, +0.7f, +0.7f),
			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.2f, +0.5f, +1.0f),

			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.6f, +1.0f, +0.7f),
			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+0.6f, +0.4f, +0.8f),
			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.2f, +0.8f, +0.7f),
			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.2f, +0.7f, +1.0f),

			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.8f, +0.3f, +0.7f),
			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.8f, +0.9f, +0.5f),
			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.5f, +0.8f, +0.5f),
			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.9f, +1.0f, +0.2f),
		};

		ret.num_vertices = NUM_ARRAY_ELEMENTS(cube_verts);
		ret.vertices = new Vertex[ret.num_vertices];
		memcpy(ret.vertices, cube_verts, sizeof(cube_verts));

		unsigned short cube_indices[] = {
			0, 1, 2, 0, 2, 3, // Top
			4, 5, 6, 4, 6, 7, // Front
			8, 9, 10, 8, 10, 11, // Right
			12, 13, 14, 12, 14, 15, // Left
			16, 17, 18, 16, 18, 19, // Back
			20, 22, 21, 20, 23, 22, // Bottom
		};

		ret.num_indices = NUM_ARRAY_ELEMENTS(cube_indices);
		ret.indices = new GLushort[ret.num_indices];
		memcpy(ret.indices, cube_indices, sizeof(cube_indices));

		return ret;
	}
}