#ifndef VE_MATH_MATRIX_2D_H
#define VE_MATH_MATRIX_2D_H

#include "Voyager/Math/Vector/Vector2.h"
#include <cmath>

namespace VE 
{
	namespace Math
	{
		struct Matrix2D
		{
			float m[2][2];

			inline explicit Matrix2D(
				float _00 = 1, float _01 = 0,
				float _10 = 0, float _11 = 1);

			// Factory function - feed angle in radians and will yield a matrix 
			// that can be applied to a vector to perform a rotation.
			inline static Matrix2D rotate(float radians);
		};

		// The left hand is a matrix.
		inline Vector2 operator*(
			const Matrix2D& matrix,
			const Vector2& vector);

#include "Voyager/Math/Matrix/Matrix2D.inl"
	}
}

#endif
