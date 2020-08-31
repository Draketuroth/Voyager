
#include "Voyager/Geometry/GeometryGenerator.h"

#include "Voyager/Core/Log.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a);

namespace VE 
{
	namespace Geometry
	{
		GeometryData GeometryGenerator::makeTriangle()
		{
			GeometryData data;

			float positions[] =
			{
				+0.0f, +1.0f, +0.0f, // Top
				-1.0f, -1.0f, +0.0f, // Lower left
				+1.0f, -1.0f, +0.0f  // Lower right
			};
			float normals[] =
			{
				+0.0f, +0.0f, +1.0f, // Top
				+0.0f, +0.0f, +1.0f, // Lower left
				+0.0f, +0.0f, +1.0f  // Lower right
			};
			float uvs[] =
			{
				+0.5f, +1.0f, // Top
				+0.0f, +0.0f, // Lower left
				+1.0f, +0.0f  // Lower right
			};

			data.positions.insert(data.positions.begin(), std::begin(positions), std::end(positions));
			data.normals.insert(data.normals.begin(), std::begin(normals), std::end(normals));
			data.uvs.insert(data.uvs.begin(), std::begin(uvs), std::end(uvs));

			unsigned int indices[] = { 0, 1, 2 };
			data.indices.insert(data.indices.begin(), std::begin(indices), std::end(indices));

			return data;
		}

		GeometryData GeometryGenerator::makeCube()
		{
			GeometryData data;

			float positions[] =
			{
				// Top face
				-1.0f, +1.0f, +1.0f,
				+1.0f, +1.0f, +1.0f,
				+1.0f, +1.0f, -1.0f,
				-1.0f, +1.0f, -1.0f,

				// Back face
				-1.0f, +1.0f, -1.0f,
				+1.0f, +1.0f, -1.0f,
				+1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,

				// Left face
				+1.0f, +1.0f, -1.0f,
				+1.0f, +1.0f, +1.0f,
				+1.0f, -1.0f, +1.0f,
				+1.0f, -1.0f, -1.0f,

				// Right face
				-1.0f, +1.0f, +1.0f,
				-1.0f, +1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f, +1.0f,

				// Front face
				+1.0f, +1.0f, +1.0f,
				-1.0f, +1.0f, +1.0f,
				-1.0f, -1.0f, +1.0f,
				+1.0f, -1.0f, +1.0f,

				// Bottom face
				+1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f, +1.0f,
				+1.0f, -1.0f, +1.0f,
			};
			float normals[] =
			{
				// Top face
				+0.0f, +1.0f, +0.0f,
				+0.0f, +1.0f, +0.0f,
				+0.0f, +1.0f, +0.0f,
				+0.0f, +1.0f, +0.0f,

				// Back face
				+0.0f, +0.0f, -1.0f,
				+0.0f, +0.0f, -1.0f,
				+0.0f, +0.0f, -1.0f,
				+0.0f, +0.0f, -1.0f,

				// Left face
				+1.0f, +0.0f, +0.0f,
				+1.0f, +0.0f, +0.0f,
				+1.0f, +0.0f, +0.0f,
				+1.0f, +0.0f, +0.0f,

				// Right face
				-1.0f, +0.0f, +0.0f,
				-1.0f, +0.0f, +0.0f,
				-1.0f, +0.0f, +0.0f,
				-1.0f, +0.0f, +0.0f,

				// Front face
				+0.0f, +0.0f, +1.0f,
				+0.0f, +0.0f, +1.0f,
				+0.0f, +0.0f, +1.0f,
				+0.0f, +0.0f, +1.0f,

				// Bottom face
				+0.0f, -1.0f, +0.0f,
				+0.0f, -1.0f, +0.0f,
				+0.0f, -1.0f, +0.0f,
				+0.0f, -1.0f, +0.0f,
			};
			float uvs[] =
			{
				// Top face
				+0.0f, +1.0f,
				+1.0f, +1.0f,
				+1.0f, +0.0f,
				+0.0f, +0.0f,

				// Back face
				+1.0f, +0.0f,
				+0.0f, +0.0f,
				+0.0f, +1.0f,
				+1.0f, +1.0f,

				// Left face
				+1.0f, +0.0f,
				+0.0f, +0.0f,
				+0.0f, +1.0f,
				+1.0f, +1.0f,

				// Right face
				+1.0f, +0.0f,
				+0.0f, +0.0f,
				+0.0f, +1.0f,
				+1.0f, +1.0f,

				// Front face
				+1.0f, +0.0f,
				+0.0f, +0.0f,
				+0.0f, +1.0f,
				+1.0f, +1.0f,

				// Bottom face
				+1.0f, +1.0f,
				+0.0f, +1.0f,
				+0.0f, +0.0f,
				+1.0f, +0.0f
			};

			data.positions.insert(data.positions.begin(), std::begin(positions), std::end(positions));
			data.normals.insert(data.normals.begin(), std::begin(normals), std::end(normals));
			data.uvs.insert(data.uvs.begin(), std::begin(uvs), std::end(uvs));

			unsigned int indices[] = {
				0, 1, 2, 0, 2, 3, // Top
				4, 5, 6, 4, 6, 7, // Front
				8, 9, 10, 8, 10, 11, // Right
				12, 13, 14, 12, 14, 15, // Left
				16, 17, 18, 16, 18, 19, // Back
				20, 22, 21, 20, 23, 22, // Bottom
			};
			data.indices.insert(data.indices.begin(), std::begin(indices), std::end(indices));

			return data;
		}

		GeometryData GeometryGenerator::makePlane(unsigned int dimensions)
		{
			//////////////////////////////
			// VERTICES
			//////////////////////////////
			GeometryData data;

			unsigned int numVertices = dimensions * dimensions;
			unsigned int half = dimensions / 2;

			data.positions.resize(numVertices);
			data.normals.resize(numVertices);
			data.uvs.resize(numVertices);

			float lowest = 0.0f - half;
			float highest = half - 1.0f;

			float range = (lowest - highest) * -1;
			float offset = 0.0f - lowest;

			for (unsigned int i = 0; i < dimensions; i++)
			{
				for (unsigned int j = 0; j < dimensions; j++)
				{
					unsigned int index = i * dimensions + j;

					data.positions[index].x = j - static_cast<float>(half);
					data.positions[index].z = i - static_cast<float>(half);
					data.positions[index].y = 0;

					data.normals[index].x = 0.0f;
					data.normals[index].y = 1.0f;
					data.normals[index].z = 0.0f;

					float abs_x = data.positions[index].x + offset;
					float abs_y = data.positions[index].z + offset;

					data.uvs[index].x = abs_x / range;
					data.uvs[index].y = abs_y / range;
				}
			}

			//////////////////////////////
			// INDICES
			//////////////////////////////
			unsigned int numIndices = (dimensions - 1) * (dimensions - 1) * 2 * 3; // 2 triangles per square, 3 indices per triangle
			data.indices.resize(numIndices);

			int runner = 0;
			for (unsigned int row = 0; row < dimensions - 1; row++)
			{
				for (unsigned int col = 0; col < dimensions - 1; col++)
				{
					data.indices[runner++] = dimensions * row + col;
					data.indices[runner++] = dimensions * row + col + dimensions;
					data.indices[runner++] = dimensions * row + col + dimensions + 1;

					data.indices[runner++] = dimensions * row + col;
					data.indices[runner++] = dimensions * row + col + dimensions + 1;
					data.indices[runner++] = dimensions * row + col + 1;
				}
			}

			// Runner should have iterated throuch each index...
			VE_CORE_ASSERT(runner == numIndices, "Failed to generate plane indices");

			return data;
		}

		GeometryData GeometryGenerator::generateNormals(const GeometryData& data)
		{
			GeometryData outData;
			unsigned int inDataPosCount = data.positions.size();
			unsigned int numVertices = inDataPosCount * 2;	// Start point and end-point for each normal.
			outData.positions.resize(numVertices);

			for (unsigned int i = 0; i < inDataPosCount; i++)
			{
				unsigned int index = i * 2;
				Math::Vector3D& v1 = outData.positions[index];
				Math::Vector3D& v2 = outData.positions[index + 1];
				const Math::Vector3D& inDataPos = data.positions[i];
				const Math::Vector3D& inDataNormal = data.normals[i];
				v1 = inDataPos;
				v2 = inDataPos + inDataNormal;
			}
			unsigned int numIndices = outData.positions.size();
			outData.indices.resize(numIndices);
			for (unsigned int i = 0; i < numIndices; i++)
			{
				outData.indices[i] = i;
			}
			return outData;
		}
		void GeometryGenerator::generateBarycentric(GeometryData* data)
		{
			if (data) 
			{
				unsigned int numPositions = data->positions.size();

				data->barycentric.clear();
				for (unsigned int index = 0; index < numPositions; index += 3)
				{
					data->barycentric.push_back(Math::Vector3D(1.0f, 0.0f, 0.0f));
					data->barycentric.push_back(Math::Vector3D(0.0f, 1.0f, 0.0f));
					data->barycentric.push_back(Math::Vector3D(0.0f, 0.0f, 1.0f));
				}
			}
			else 
			{
				// Log...
			}
		}
	}
}
