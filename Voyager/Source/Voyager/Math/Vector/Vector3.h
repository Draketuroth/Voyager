#ifndef VE_MATH_VECTOR_3_H
#define VE_MATH_VECTOR_3_H
#include <cmath>

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/VectorLayout.h"

namespace VE 
{
	namespace Math
	{
		struct Vector3 : public Vector::Base<Vector::LayoutXYZ>
		{
			inline Vector3(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0) 
			{
				x = xIn;
				y = yIn;
				z = zIn;
			}

			inline Vector3(const Vector::Base<Vector::LayoutXYZ>& other);
		};

		inline Vector3 cross(const Vector3& a, const Vector3& b);

#include "Voyager/Math/Vector/Vector3.inl"
	}
}

#endif