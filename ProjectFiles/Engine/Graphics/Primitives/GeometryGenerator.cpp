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
using glm::vec4;

namespace Graphics
{
	Geometry GeometryGenerator::makeTriangle()
	{
		Geometry ret;
		Vertex verts[] =
		{
			vec3(+0.0f, +1.0f, +0.0f),
			vec3(+1.0f, +0.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),

			vec3(-1.0f, -1.0f, +0.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),

			vec3(+1.0f, -1.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),
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
			vec3(+0.0f, +1.0f, +0.0f),

			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec3(+0.0f, +1.0f, +0.0f),

			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec3(+0.0f, +1.0f, +0.0f),

			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +1.0f, +0.0f),


			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+1.0f, +0.0f, +1.0f),
			vec3(+0.0f, +0.0f, -1.0f),

			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +0.5f, +0.2f),
			vec3(+0.0f, +0.0f, -1.0f),

			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.8f, +0.6f, +0.4f),
			vec3(+0.0f, +0.0f, -1.0f),

			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.3f, +1.0f, +0.5f),
			vec3(+0.0f, +0.0f, -1.0f),



			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.2f, +0.5f, +0.2f),
			vec3(+1.0f, +0.0f, +0.0f),

			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.9f, +0.3f, +0.7f),
			vec3(+1.0f, +0.0f, +0.0f),

			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.3f, +0.7f, +0.5f),
			vec3(+1.0f, +0.0f, +0.0f),

			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.5f, +0.7f, +0.5f),
			vec3(+1.0f, +0.0f, +0.0f),



			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+0.7f, +0.8f, +0.2f),
			vec3(-1.0f, +0.0f, +0.0f),

			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+0.5f, +0.7f, +0.3f),
			vec3(-1.0f, +0.0f, +0.0f),

			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.4f, +0.7f, +0.7f),
			vec3(-1.0f, +0.0f, +0.0f),

			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.2f, +0.5f, +1.0f),
			vec3(-1.0f, +0.0f, +0.0f),


			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.6f, +1.0f, +0.7f),
			vec3(+0.0f, +0.0f, +1.0f),

			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+0.6f, +0.4f, +0.8f),
			vec3(+0.0f, +0.0f, +1.0f),

			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.2f, +0.8f, +0.7f),
			vec3(+0.0f, +0.0f, +1.0f),

			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.2f, +0.7f, +1.0f),
			vec3(+0.0f, +0.0f, +1.0f),



			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.8f, +0.3f, +0.7f),
			vec3(+0.0f, -1.0f, +0.0f),

			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.8f, +0.9f, +0.5f),
			vec3(+0.0f, -1.0f, +0.0f),

			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.5f, +0.8f, +0.5f),
			vec3(+0.0f, -1.0f, +0.0f),

			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.9f, +1.0f, +0.2f),
			vec3(+0.0f, -1.0f, +0.0f),
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
			vec3(+0.00f, +1.00f, +0.00f),

			vec3(+0.50f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			vec3(+0.00f, +0.25f, -1.00f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			vec3(-0.50f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			// Bottom side of arrow head.
			vec3(+0.00f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			vec3(+0.50f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			vec3(+0.00f, -0.25f, -1.00f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			vec3(-0.50f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			// Right side of arrow tip.
			vec3(+0.50f, +0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(0.83205032f, 0.00f, -0.55470026f),

			vec3(+0.00f, +0.25f, -1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(0.83205032f, 0.00f, -0.55470026f),

			vec3(+0.00f, -0.25f, -1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(0.83205032f, 0.00f, -0.55470026f),

			vec3(+0.50f, -0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(0.83205032f, 0.00f, -0.55470026f),

			// Left side of arrow tip.
			vec3(+0.00f, +0.25f, -1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.55708605f, 0.00f, -0.37139067f),

			vec3(-0.50f, +0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.55708605f, 0.00f, -0.37139067f),

			vec3(+0.00f, -0.25f, -1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.55708605f, 0.00f, -0.37139067f),

			vec3(-0.50f, -0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-0.55708605f, 0.00f, -0.37139067f),

			// Back side of arrow tip.
			vec3(-0.50f, +0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			vec3(+0.50f, +0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			vec3(-0.50f, -0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			vec3(+0.50f, -0.25f, -0.25f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			// Top side of back of arrow.
			vec3(+0.25f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			vec3(+0.25f, +0.25f, +1.00f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			vec3(-0.25f, +0.25f, +1.00f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			vec3(-0.25f, +0.25f, -0.25f),
			vec3(+1.00f, +0.00f, +0.00f),
			vec3(+0.00f, +1.00f, +0.00f),

			// Bottom side of back of arrow.
			vec3(+0.25f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			vec3(+0.25f, -0.25f, +1.00f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			vec3(-0.25f, -0.25f, +1.00f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			vec3(-0.25f, -0.25f, -0.25f),
			vec3(+0.00f, +0.00f, +1.00f),
			vec3(+0.00f, -1.00f, +0.00f),

			// Right side of back of arrow.
			vec3(+0.25f, +0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+1.00f, +0.00f, +0.00f),

			vec3(+0.25f, -0.25f, -0.25f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+1.00f, +0.00f, +0.00f),

			vec3(+0.25f, -0.25f, +1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+1.00f, +0.00f, +0.00f),

			vec3(+0.25f, +0.25f, +1.00f),
			vec3(+0.60f, +1.00f, +0.00f),
			vec3(+1.00f, +0.00f, +0.00f),

			// Left side of back of arrow.
			vec3(-0.25f, +0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-1.00f, +0.00f, +0.00f),

			vec3(-0.25f, -0.25f, -0.25f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-1.00f, +0.00f, +0.00f),

			vec3(-0.25f, -0.25f, +1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-1.00f, +0.00f, +0.00f),

			vec3(-0.25f, +0.25f, +1.00f),
			vec3(+0.00f, +1.00f, +0.00f),
			vec3(-1.00f, +0.00f, +0.00f),

			// Back side of back of arrow.
			vec3(-0.25f, +0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			vec3(+0.25f, +0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			vec3(-0.25f, -0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),

			vec3(+0.25f, -0.25f, +1.00f),
			vec3(+0.50f, +0.50f, +0.50f),
			vec3(+0.00f, +0.00f, +1.00f),
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

	Geometry GeometryGenerator::makePlane(unsigned int dimensions)
	{
		Geometry ret = makePlaneVerts(dimensions);
		Geometry ret2 = makePlaneIndices(dimensions);
		ret.num_indices = ret2.num_indices;
		ret.indices = ret2.indices;
		return ret;
	}

	Geometry GeometryGenerator::makePlaneVerts(unsigned int dimensions)
	{
		Geometry ret;
		ret.num_vertices = dimensions * dimensions;
		int half = dimensions / 2;
		ret.vertices = new Vertex[ret.num_vertices];
		for (int i = 0; i < dimensions; i++)
		{
			for (int j = 0; j < dimensions; j++)
			{
				Vertex& current_vert = ret.vertices[i * dimensions + j];
				current_vert.position.x = j - half;
				current_vert.position.z = i - half;
				current_vert.position.y = 0;
				current_vert.normal = vec3(0.0f, 1.0f, 0.0f);
				current_vert.color.x = rand() / (float)RAND_MAX;
				current_vert.color.y = rand() / (float)RAND_MAX;
				current_vert.color.z = rand() / (float)RAND_MAX;
			}
		}
		return ret;
	}

	Geometry GeometryGenerator::makePlaneIndices(unsigned int dimensions)
	{
		Geometry ret;
		ret.num_indices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
		ret.indices = new unsigned short[ret.num_indices];
		int runner = 0;
		for (int row = 0; row < dimensions - 1; row++)
		{
			for (int col = 0; col < dimensions - 1; col++)
			{
				ret.indices[runner++] = dimensions * row + col;
				ret.indices[runner++] = dimensions * row + col + dimensions;
				ret.indices[runner++] = dimensions * row + col + dimensions + 1;

				ret.indices[runner++] = dimensions * row + col;
				ret.indices[runner++] = dimensions * row + col + dimensions + 1;
				ret.indices[runner++] = dimensions * row + col + 1;
			}
		}
		assert(runner == ret.num_indices);
		return ret;
	}

	Geometry GeometryGenerator::generateNormals(const Geometry& data)
	{
		Geometry ret;
		ret.num_vertices = data.num_vertices * 2;	// Start point and end-point for each normal.
		ret.vertices = new Vertex[ret.num_vertices];
		vec4 white(1.0f, 1.0f, 1.0f, 1.0f);
		for (int i = 0; i < data.num_vertices; i++)
		{
			unsigned int vertex_index = i * 2;
			Vertex& v1 = ret.vertices[vertex_index];
			Vertex& v2 = ret.vertices[vertex_index + 1];
			const Vertex& source_vertex = data.vertices[i];
			v1.position = source_vertex.position;
			v2.position = source_vertex.position + source_vertex.normal;
			v1.color = v2.color = white;
		}
		ret.num_indices = ret.num_vertices;
		ret.indices = new GLushort[ret.num_indices];
		for (int i = 0; i < ret.num_indices; i++)
		{
			ret.indices[i] = i;
		}
		return ret;
	}
}