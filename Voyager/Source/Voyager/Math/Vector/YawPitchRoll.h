#ifndef VE_MATH_YAW_PITCH_ROLL_H
#define VE_MATH_YAW_PITCH_ROLL_H

namespace VE 
{
	namespace Math 
	{
		struct YawPitchRoll
		{
			YawPitchRoll() : yaw(0.0), pitch(0.0), roll(0.0) {}
			YawPitchRoll(float y, float p, float r) : yaw(y), pitch(p), roll(r) {}
			float yaw;
			float pitch;
			float roll;
		};

#include "Voyager/Math/Vector/YawPitchRoll.inl"
	}
}

#endif