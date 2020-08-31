#ifndef VE_MATH_ROTATION_H
#define VE_MATH_ROTATION_H

namespace VE 
{
	namespace Math 
	{
		struct YawPitchRoll
		{
			YawPitchRoll() : yaw(0.0), pitch(0.0), roll(0.0) {}
			YawPitchRoll(double y, double p, double r) : yaw(y), pitch(p), roll(r) {}
			float yaw;
			float pitch;
			float roll;
		};

#include "Voyager/Math/Vector/Rotation.h"
	}
}

#endif