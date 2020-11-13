#ifndef VE_MATH_MATRIX_3X3_H
#define VE_MATH_MATRIX_3X3_H

#include "Voyager/Math/Matrix/Base.h"
#include "Voyager/Math/Matrix/MatrixLayout.h"

#include "Voyager/Math/Vector/Vector3.h"

namespace VE 
{
	namespace Math
	{
		struct Matrix3x3 : public Matrix::Base<Matrix::Layout3x3>
		{
			inline Matrix3x3(
				float _00 = 1, float _01 = 0, float _02 = 0,
				float _10 = 0, float _11 = 1, float _12 = 0,
				float _20 = 0, float _21 = 0, float _22 = 1) 
			{
				m[0][0] = _00;
				m[0][1] = _01;
				m[0][2] = _02;

				m[1][0] = _10;
				m[1][1] = _11;
				m[1][2] = _12;

				m[2][0] = _20;
				m[2][1] = _21;
				m[2][2] = _22;
			}

			inline Matrix3x3(float(&mat)[4][4]);

			inline static Matrix3x3 rotateZ(float radians);
			inline static Matrix3x3 translate(float x, float y);
			inline static Matrix3x3 scale(float x, float y);
		};

		inline Vector3 operator*(const Vector3& vector, const Matrix3x3& matrix);
		inline Matrix3x3 operator*(const Matrix3x3& left, const Matrix3x3& right);

#include "Voyager/Math/Matrix/Matrix3x3.inl"
	}
}

#endif