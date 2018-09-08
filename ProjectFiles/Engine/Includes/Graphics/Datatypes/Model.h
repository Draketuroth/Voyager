//============================================================================
// # VOYAGER ENGINE #
// Name: Model.h
// Module: Graphics
// Author: Fredrik Linde
// Created on: Sep 8, 2018
// Description: Struct for Model View Component pattern.
//============================================================================

#ifndef VE_GRAPHICS_MODEL_H
#define VE_GRAPHICS_MODEL_H

#include <glm.hpp>

namespace Graphics
{
	struct Model
	{
		glm::vec3 light_position;
	};
}

#endif
