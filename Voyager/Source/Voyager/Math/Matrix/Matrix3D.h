#ifndef VE_MATH_MATRIX_3D_H
#define VE_MATH_MATRIX_3D_H

#include "Voyager/Math/Vector/Vector3.h"

namespace VE 
{
	namespace Math
	{
		struct Matrix3D
		{
			float m[3][3];

			inline Matrix3D(
				float _00 = 1, float _01 = 0, float _02 = 0,
				float _10 = 0, float _11 = 1, float _12 = 0,
				float _20 = 0, float _21 = 0, float _22 = 1);

			inline Matrix3D(float(&mat)[4][4]);

			inline static Matrix3D rotateZ(float radians);
			inline static Matrix3D translate(float x, float y);
			inline static Matrix3D scale(float x, float y);
		};

		inline Vector3 operator*(const Vector3& vector, const Matrix3D& matrix);
		inline Matrix3D operator*(const Matrix3D& left, const Matrix3D& right);

#include "Voyager/Math/Matrix/Matrix3D.inl"
	}
}

#endif