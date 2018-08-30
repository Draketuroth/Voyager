//============================================================================
// # VOYAGER ENGINE #
// Name: TestingHelper.h
// Module: Testing
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Helper functions for testing
//============================================================================

#ifndef VE_TESTING_TESTING_HELPER_H
#define VE_TESTING_TESTING_HELPER_H
#include <cmath>

inline bool proximate(
	float left, float right,
	float threshold = 0.0000001)
{
	return abs(left - right) < threshold;
}

#endif
