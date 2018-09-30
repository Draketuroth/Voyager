//============================================================================
// # VOYAGER ENGINE #
// Name: Utilz.h
// Module: Math
// Author: Fredrik Linde
// Created on: Sep 30, 2018
// Description: Voyager utility functions.
//============================================================================

#ifndef VE_MATH_UTILZ_H
#define VE_MATH_UTILZ_H

#include <algorithm>

namespace Math
{
	// TODO: Find more appropriate location for utility functions. 

	float lerp(float min, float max, float factor);

	float clamp(float value, float lower, float upper);

#include <Math/Utilz.inl>
}

#endif
