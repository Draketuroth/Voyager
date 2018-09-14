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
#include <Core/Misc/TypeDefs.h>

namespace Graphics
{
	class GeometryGenerator
	{
	public:
		static Geometry makeTriangle();
		static Geometry makeCube();
		static Geometry makePlane(uint dimensions = 10);
		static Geometry generateNormals(const Geometry& data);

	private:
		static Geometry makePlaneVerts(uint dimensions);
		static Geometry makePlaneIndices(uint dimensions);
	};
}

#endif