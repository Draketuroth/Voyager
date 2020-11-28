#ifndef VE_MATH_MATRIX_2X2_H
#define VE_MATH_MATRIX_2X2_H

#include "Voyager/Math/Matrix/Base.h"
#include "Voyager/Math/Matrix/MatrixLayout.h"

#include "Voyager/Math/Vector/Vector2.h"

#include <cmath>

namespace VE 
{
	namespace Math
	{
		struct Matrix2x2 : public Matrix::Base<Matrix::Layout2x2>
		{
			inline explicit Matrix2x2(
				float _00 = 1, float _01 = 0,
				float _10 = 0, float _11 = 1)
			{
				m[0][0] = _00;
				m[0][1] = _01;

				m[1][0] = _10;
				m[1][1] = _11;
			}

			inline Matrix2x2(const Matrix::Base<Matrix::Layout2x2>& other)
			{
				m[0][0] = other.m[0][0];
				m[0][1] = other.m[0][1];

				m[1][0] = other.m[1][0];
				m[1][1] = other.m[1][1];
			}

			// Factory function - feed angle in radians and will yield a matrix 
			// that can be applied to a vector to perform a rotation.
			inline static Matrix2x2 rotate(float radians);
		};

		// The left hand is a matrix.
		inline Vector2 operator*(
			const Matrix2x2& matrix,
			const Vector2& vector);

#include "Voyager/Math/Matrix/Matrix2x2.inl"
	}
}

#endif
