#ifndef VE_GEOMETRYGENERATOR_H
#define VE_GEOMETRYGENERATOR_H

#include "Voyager/Geometry/GeometryData.h"

namespace VE 
{
	namespace Geometry 
	{
		class GeometryGenerator
		{
		public:
			static GeometryData makeTriangle();
			static GeometryData makeCube();
			static GeometryData makePlane(unsigned int dimensions = 10);
			static GeometryData generateNormals(const GeometryData& data);
			static void generateBarycentric(GeometryData* data);
		};
	}
}

#endif