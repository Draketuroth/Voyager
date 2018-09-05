//============================================================================
// # VOYAGER ENGINE #
// Name: GeometryGenerator.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 31, 2018
// Description: Geometry factory class
//============================================================================

#ifndef VE_GRAPHICS_GEOMETRYGENERATOR_H
#define VE_GRAPHICS_GEOMETRYGENERATOR_H

#include <Graphics/Rendering/Geometry.h>

namespace Graphics
{
	class GeometryGenerator
	{
	public:
		static Geometry makeTriangle();
		static Geometry makeCube();
		static Geometry makeArrow();
		static Geometry makePlane(unsigned int dimensions = 10);
		static Geometry generateNormals(const Geometry& data);

	private:
		static Geometry makePlaneVerts(unsigned int dimensions);
		static Geometry makePlaneIndices(unsigned int dimensions);
	};
}

#endif