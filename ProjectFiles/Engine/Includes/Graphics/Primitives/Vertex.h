//============================================================================
// # VOYAGER ENGINE #
// Name: Vertex.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Aug 30, 2018
// Description: Voyager vertex datatypes
//============================================================================

#ifndef VE_GRAPHICS_VERTEX_H
#define VE_GRAPHICS_VERTEX_H

#include <Math/Vector/Vector3D.h>
#include <glm.hpp>

namespace Graphics
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
	};
}

#endif