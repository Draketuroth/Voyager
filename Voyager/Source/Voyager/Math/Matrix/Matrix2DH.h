#ifndef VE_MATH_MATRIX_2DH_H
#define VE_MATH_MATRIX_2DH_H

#include "Voyager/Math/Vector/Vector3D.h"

namespace VE 
{
	namespace Math
	{
		// Row major
		struct Matrix2DH
		{
			float m[2][3];

			inline Matrix2DH(
				float _00 = 1, float _01 = 0, float _02 = 0,
				float _10 = 0, float _11 = 1, float _12 = 0);
			inline static Matrix2DH rotateZ(float radians);
			inline static Matrix2DH translate(float x, float y);
			inline static Matrix2DH scale(float x, float y);
		};

		inline Vector3D operator*(const Matrix2DH& matrix, const Vector3D& vector);
		inline Matrix2DH operator*(const Matrix2DH& left, const Matrix2DH& right);

#include "Voyager/Math/Matrix/Matrix2DH.inl"
	}
}

#endif