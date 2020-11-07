#ifndef VE_MATH_VECTOR_2_H
#define VE_MATH_VECTOR_2_H

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/VectorLayout.h"

namespace VE 
{
	namespace Math
	{
		struct Vector2 : public Vector::Base<Vector::LayoutXY>
		{
			inline Vector2(float xIn = 0.0f, float yIn = 0.0f)
			{
				x = xIn;
				y = yIn;
			}

			inline Vector2(const Vector::Base<Vector::LayoutXY>& other);
		};

#include "Voyager/Math/Vector/Vector2.inl"
	}
}

#endif
