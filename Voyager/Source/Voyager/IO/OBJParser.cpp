
#include "Voyager/IO/OBJParser.h"

#include "Voyager/Core/Log.h"

#include "Voyager/Geometry/GeometryGenerator.h"

#include "Voyager/Math/Vector/Vector3D.h"
#include "Voyager/Math/Vector/Vector2D.h"

namespace VE 
{
	namespace IO
	{
		namespace OBJ
		{
			namespace
			{
				struct OBJParser final
				{
					std::string path;

					OBJParser(const std::string& filePath) : path(filePath)
					{

					}

					VE::Geometry::GeometryData parseOBJ()
					{
						// Temporary in vectors used to compile final model data.
						std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
						std::vector<Math::Vector3D> inVertices;
						std::vector<Math::Vector2D> inUVs;
						std::vector<Math::Vector3D> inNormals;

						std::ifstream input(path);
						for (std::string line; getline(input, line); )
						{
							std::stringstream linestream(line);
							std::string lineHeader;

							std::getline(linestream, lineHeader, ' ');

							if (lineHeader == "v") {
								VE::Math::Vector3D vertex;
								linestream >> vertex.x >> vertex.y >> vertex.z;
								inVertices.push_back(vertex);
							}
							else if (lineHeader == "vt") 
							{
								VE::Math::Vector2D uv;
								linestream >> uv.x >> uv.y;
								inUVs.push_back(uv);
							}
							else if (lineHeader == "vn") {
								VE::Math::Vector3D normal;
								linestream >> normal.x >> normal.y >> normal.z;
								inNormals.push_back(normal);
							}
							else if (lineHeader == "usemtl") 
							{

							}
							else if (lineHeader == "f") 
							{
								unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
								for (unsigned int index = 0; index < 3; index++) 
								{
									std::string vertex;
									char ch;

									linestream >> vertex;
									std::stringstream indexStream(vertex);
									indexStream >> vertexIndex[index] >> ch >> uvIndex[index] >> ch >> normalIndex[index];
								}
								vertexIndices.push_back(vertexIndex[0]);
								vertexIndices.push_back(vertexIndex[1]);
								vertexIndices.push_back(vertexIndex[2]);
								uvIndices.push_back(uvIndex[0]);
								uvIndices.push_back(uvIndex[1]);
								uvIndices.push_back(uvIndex[2]);
								normalIndices.push_back(normalIndex[0]);
								normalIndices.push_back(normalIndex[1]);
								normalIndices.push_back(normalIndex[2]);
							}
						}

						// Construct model data from file content.
						VE::Geometry::GeometryData data;
						
						for (unsigned int i = 0; i < vertexIndices.size(); i++)
						{
							unsigned int vertexIndex = vertexIndices[i];
							Math::Vector3D vertex = inVertices[vertexIndex - 1];
							data.positions.push_back(vertex);
						}
						for (unsigned int i = 0; i < uvIndices.size(); i++)
						{
							unsigned int uvIndex = uvIndices[i];
							Math::Vector2D uv = inUVs[uvIndex - 1];
							data.uvs.push_back(uv);
						}
						for (unsigned int i = 0; i < normalIndices.size(); i++)
						{
							unsigned int normalIndex = normalIndices[i];
							Math::Vector3D normal = inNormals[normalIndex - 1];
							data.normals.push_back(normal);
						}

						VE::Geometry::GeometryGenerator::generateBarycentric(&data);

						// Finalize data for GPU.
						data.interleave();

						return data;
					}
				};
			}

			VE::Geometry::GeometryData parse(const std::string& in)
			{
				OBJParser parser(in);
				VE::Geometry::GeometryData result = parser.parseOBJ();

				return result;
			}
		}
	}
}