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
using glm::vec3;

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

	Geometry GeometryGenerator::makeArrow()
	{
		Geometry ret;
		Vertex arrow_verts[] =
		{
			// Top side of arrow head.
			vec3(+0.00f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.50f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +0.25f, -1.00f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(-0.50f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),

			// Bottom side of arrow head.
			vec3(+0.00f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.50f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -0.25f, -1.00f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(-0.50f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),

			// Right side of arrow tip.
			vec3(+0.50f, +0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+0.00f, +0.25f, -1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+0.00f, -0.25f, -1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+0.50f, -0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),

			// Left side of arrow tip.
			vec3(+0.00f, +0.25f, -1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.50f, +0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(+0.00f, -0.25f, -1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.50f, -0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),

			// Back side of arrow tip.
			vec3(-0.50f, +0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.50f, +0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(-0.50f, -0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.50f, -0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),

			// Top side of back of arrow.
			vec3(+0.25f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.25f, +0.25f, +1.00f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(-0.25f, +0.25f, +1.00f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(-0.25f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),

			// Bottom side of back of arrow.
			vec3(+0.25f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.25f, -0.25f, +1.00f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(-0.25f, -0.25f, +1.00f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(-0.25f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),

			// Right side of back of arrow.
			vec3(+0.25f, +0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+0.25f, -0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+0.25f, -0.25f, +1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+0.25f, +0.25f, +1.00f),
			vec3(+0.60f, +1.00f, +0.00f),

			// Left side of back of arrow.
			vec3(-0.25f, +0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.25f, -0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.25f, -0.25f, +1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.25f, +0.25f, +1.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			// Back side of back of arrow.
			vec3(-0.25f, +0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.25f, +0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(-0.25f, -0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.25f, -0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
		};
		GLushort arrow_indices[] = {
			0, 1, 2,
			0, 2, 3,
			4, 6, 5,
			4, 7, 6,
			8, 10, 9,
			8, 11, 10,
			12, 15, 13,
			12, 14, 15,
			16, 19, 17,
			16, 18, 19,
			20, 22, 21,
			20, 23, 22,
			24, 25, 26,
			24, 26, 27,
			28, 30, 29,
			28, 31, 30,
			32, 33, 34,
			32, 34, 35,
			36, 39, 37,
			36, 38, 39,
		};
		ret.num_vertices = sizeof(arrow_verts) / sizeof(*arrow_verts);
		ret.vertices = new Vertex[ret.num_vertices];
		memcpy(ret.vertices, arrow_verts, sizeof(arrow_verts));
		ret.num_indices = sizeof(arrow_indices) / sizeof(*arrow_indices);
		ret.indices = new GLushort[ret.num_indices];
		memcpy(ret.indices, arrow_indices, sizeof(arrow_indices));
		return ret;
	}
}