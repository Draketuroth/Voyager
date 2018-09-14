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
using glm::vec2;
using glm::vec3;
using glm::vec4;

namespace Graphics
{
	Geometry GeometryGenerator::makeTriangle()
	{
		Geometry ret;
		Vertex verts[] =
		{
			// Top
			vec3(+0.0f, +1.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+0.5f, +1.0f),

			// Lower left
			vec3(-1.0f, -1.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+0.0f, +0.0f),

			// Lower right
			vec3(+1.0f, -1.0f, +0.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+1.0f, +0.0f),
		};
		ret.num_vertices = NUM_ARRAY_ELEMENTS(verts);
		ret.vertices = new Vertex[ret.num_vertices];
		memcpy(ret.vertices, verts, sizeof(verts));

		ushort indices[] = { 0, 1, 2 };
		ret.num_indices = NUM_ARRAY_ELEMENTS(indices);
		ret.indices = new ushort[ret.num_indices];
		memcpy(ret.indices, indices, sizeof(indices));

		return ret;
	}

	Geometry GeometryGenerator::makeCube()
	{
		Geometry ret;
		Vertex cube_verts[] =
		{
			// Top face
			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec2(+0.0f, +1.0f),

			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec2(+1.0f, +1.0f),

			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec2(+1.0f, +0.0f),

			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +1.0f, +0.0f),
			vec2(+0.0f, +0.0f),

			// Back face
			vec3(-1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +0.0f, -1.0f),
			vec2(+1.0f, +0.0f),

			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+0.0f, +0.0f, -1.0f),
			vec2(+0.0f, +0.0f),

			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.0f, +0.0f, -1.0f),
			vec2(+0.0f, +1.0f),

			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.0f, +0.0f, -1.0f),
			vec2(+1.0f, +1.0f),

			// Left face
			vec3(+1.0f, +1.0f, -1.0f),
			vec3(+1.0f, +0.0f, +0.0f),
			vec2(+1.0f, +0.0f),

			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+1.0f, +0.0f, +0.0f),
			vec2(+0.0f, +0.0f),

			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+1.0f, +0.0f, +0.0f),
			vec2(+0.0f, +1.0f),

			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+1.0f, +0.0f, +0.0f),
			vec2(+1.0f, +1.0f),

			// Right face
			vec3(-1.0f, +1.0f, +1.0f),
			vec3(-1.0f, +0.0f, +0.0f),
			vec2(+1.0f, +0.0f),

			vec3(-1.0f, +1.0f, -1.0f),
			vec3(-1.0f, +0.0f, +0.0f),
			vec2(+0.0f, +0.0f),

			vec3(-1.0f, -1.0f, -1.0f),
			vec3(-1.0f, +0.0f, +0.0f),
			vec2(+0.0f, +1.0f),

			vec3(-1.0f, -1.0f, +1.0f),
			vec3(-1.0f, +0.0f, +0.0f),
			vec2(+1.0f, +1.0f),

			// Front face
			vec3(+1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+1.0f, +0.0f),

			vec3(-1.0f, +1.0f, +1.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+0.0f, +0.0f),

			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+0.0f, +1.0f),

			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.0f, +0.0f, +1.0f),
			vec2(+1.0f, +1.0f),

			// Bottom face
			vec3(+1.0f, -1.0f, -1.0f),
			vec3(+0.0f, -1.0f, +0.0f),
			vec2(+1.0f, +1.0f),

			vec3(-1.0f, -1.0f, -1.0f),
			vec3(+0.0f, -1.0f, +0.0f),
			vec2(+0.0f, +1.0f),

			vec3(-1.0f, -1.0f, +1.0f),
			vec3(+0.0f, -1.0f, +0.0f),
			vec2(+0.0f, +0.0f),

			vec3(+1.0f, -1.0f, +1.0f),
			vec3(+0.0f, -1.0f, +0.0f),
			vec2(+1.0f, +0.0f),
		};

		ret.num_vertices = NUM_ARRAY_ELEMENTS(cube_verts);
		ret.vertices = new Vertex[ret.num_vertices];
		memcpy(ret.vertices, cube_verts, sizeof(cube_verts));

		ushort cube_indices[] = {
			0, 1, 2, 0, 2, 3, // Top
			4, 5, 6, 4, 6, 7, // Front
			8, 9, 10, 8, 10, 11, // Right
			12, 13, 14, 12, 14, 15, // Left
			16, 17, 18, 16, 18, 19, // Back
			20, 22, 21, 20, 23, 22, // Bottom
		};

		ret.num_indices = NUM_ARRAY_ELEMENTS(cube_indices);
		ret.indices = new ushort[ret.num_indices];
		memcpy(ret.indices, cube_indices, sizeof(cube_indices));

		return ret;
	}

	Geometry GeometryGenerator::makePlane(uint dimensions)
	{
		Geometry ret = makePlaneVerts(dimensions);
		Geometry ret2 = makePlaneIndices(dimensions);
		ret.num_indices = ret2.num_indices;
		ret.indices = ret2.indices;
		return ret;
	}

	Geometry GeometryGenerator::makePlaneVerts(uint dimensions)
	{
		Geometry ret;
		ret.num_vertices = dimensions * dimensions;
		uint half = dimensions / 2;
		ret.vertices = new Vertex[ret.num_vertices];

		float lowest = 0.0f - half;
		float highest = half - 1.0f;

		float range = (lowest - highest) * -1;
		float offset = 0.0f - lowest;

		for (uint i = 0; i < dimensions; i++)
		{
			for (uint j = 0; j < dimensions; j++)
			{
				Vertex& current_vert = ret.vertices[i * dimensions + j];
				current_vert.position.x = j - static_cast<float>(half);
				current_vert.position.z = i - static_cast<float>(half);
				current_vert.position.y = 0;
				current_vert.normal = vec3(0.0f, 1.0f, 0.0f);

				float abs_x = current_vert.position.x + offset;
				float abs_y = current_vert.position.z + offset;

				current_vert.uv.x = abs_x / range;
				current_vert.uv.y = abs_y / range;
			}
		}
		return ret;
	}

	Geometry GeometryGenerator::makePlaneIndices(uint dimensions)
	{
		Geometry ret;
		ret.num_indices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
		ret.indices = new ushort[ret.num_indices];
		int runner = 0;
		for (uint row = 0; row < dimensions - 1; row++)
		{
			for (uint col = 0; col < dimensions - 1; col++)
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
		for (uint i = 0; i < data.num_vertices; i++)
		{
			uint vertex_index = i * 2;
			Vertex& v1 = ret.vertices[vertex_index];
			Vertex& v2 = ret.vertices[vertex_index + 1];
			const Vertex& source_vertex = data.vertices[i];
			v1.position = source_vertex.position;
			v2.position = source_vertex.position + source_vertex.normal;
		}
		ret.num_indices = ret.num_vertices;
		ret.indices = new ushort[ret.num_indices];
		for (uint i = 0; i < ret.num_indices; i++)
		{
			ret.indices[i] = i;
		}
		return ret;
	}
}