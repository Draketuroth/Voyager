#ifndef VE_MATH_UTILS_H
#define VE_MATH_UTILS_H

#include <algorithm>
#include "Voyager/Math/Constants.h"

namespace VE 
{
	namespace Math
	{
		// TODO: Find more appropriate location for utility functions. 

		inline float lerp(float min, float max, float factor);

		inline float clamp(float value, float lower, float upper);

		inline float toRadians(float angleDegrees);

		inline float toDegrees(float angleRadians);

#include "Voyager/Math/Utils.inl"
	}
}

#endif
