#ifndef VE_MATH_VECTOR_3_H
#define VE_MATH_VECTOR_3_H
#include <cmath>

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/Descriptor.h"

namespace VE 
{
	namespace Math
	{
		struct Vector3 : public Vector::Base<Vector::DescXYZ>
		{
			inline Vector3(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0) 
			{
				x = xIn;
				y = yIn;
				z = zIn;
			}

			inline Vector3(const Vector::Base<Vector::DescXYZ>& other);
		};

		inline Vector3 cross(const Vector3& a, const Vector3& b);

		inline Vector3 lerp(float alpha, const Vector3& source, const Vector3& target);

#include "Voyager/Math/Vector/Vector3.inl"
	}
}

#endif