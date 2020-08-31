#ifndef VE_GEOMETRYDATA_H
#define VE_GEOMETRYDATA_H

#include <vector>

#include "Voyager/Math/Vector/Vector3D.h"
#include "Voyager/Math/Vector/Vector2D.h"

namespace VE 
{
	namespace Geometry
	{
		struct GeometryData
		{
			void interleave() 
			{
				for (unsigned int index = 0; index < positions.size(); index++)
				{
					vertices.push_back(positions[index].x);
					vertices.push_back(positions[index].y);
					vertices.push_back(positions[index].z);

					vertices.push_back(normals[index].x);
					vertices.push_back(normals[index].y);
					vertices.push_back(normals[index].z);

					vertices.push_back(barycentric[index].x);
					vertices.push_back(barycentric[index].y);
					vertices.push_back(barycentric[index].z);

					vertices.push_back(uvs[index].x);
					vertices.push_back(uvs[index].y);
				}
			}

			// Use for geometry manipulation, not to be sent to GPU!
			std::vector<Math::Vector3D> positions;
			std::vector<Math::Vector3D> normals;
			std::vector<Math::Vector3D> barycentric;
			std::vector<Math::Vector2D> uvs;

			std::vector<float> vertices; // interleaved
			std::vector<unsigned int> indices;
		};
	}
}

#endif