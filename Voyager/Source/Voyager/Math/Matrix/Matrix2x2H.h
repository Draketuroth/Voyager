#ifndef VE_MATH_MATRIX_2X2H_H
#define VE_MATH_MATRIX_2X2H_H

#include "Voyager/Math/Matrix/Base.h"
#include "Voyager/Math/Matrix/MatrixLayout.h"

#include "Voyager/Math/Vector/Vector3.h"

namespace VE
{
	namespace Math
	{
		struct Matrix2x2H : public Matrix::Base<Matrix::Layout2x3>
		{
			inline explicit Matrix2x2H(
				float _00 = 1, float _01 = 0, float _02 = 0,
				float _10 = 0, float _11 = 1, float _12 = 0)
			{
				m[0][0] = _00;
				m[0][1] = _01;
				m[0][2] = _02;

				m[1][0] = _10;
				m[1][1] = _11;
				m[1][2] = _12;
			}

			inline Matrix2x2H(const Matrix::Base<Matrix::Layout2x3>& other)
			{
				m[0][0] = other.m[0][0];
				m[0][1] = other.m[0][1];
				m[0][2] = other.m[0][2];

				m[1][0] = other.m[1][0];
				m[1][1] = other.m[1][1];
				m[1][2] = other.m[1][2];
			}

			inline static Matrix2x2H rotateZ(float radians);
			inline static Matrix2x2H translate(float x, float y);
			inline static Matrix2x2H scale(float x, float y);
		};

		inline Vector3 operator*(const Matrix2x2H& matrix, const Vector3& vector);

#include "Voyager/Math/Matrix/Matrix2x2H.inl"
	}
}

#endif