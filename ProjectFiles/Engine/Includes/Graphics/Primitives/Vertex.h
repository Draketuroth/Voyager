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
#ifdef OPENGL_ACTIVE_RENDERER
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;
	};
#else
	struct Vertex
	{
		Math::Vector3D position;
		Math::Vector3D color;
	};
#endif
}

#endif