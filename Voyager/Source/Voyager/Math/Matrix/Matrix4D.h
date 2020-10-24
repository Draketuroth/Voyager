#ifndef VE_MATH_MATRIX_4D_H
#define VE_MATH_MATRIX_4D_H

#include "Voyager/Math/Vector/Vector4.h"
#include "Voyager/Math/Vector/Vector3.h"
#include "Voyager/Math/Utils.h"

#include <algorithm>

namespace VE 
{
	namespace Math
	{
		struct Matrix4D 
		{
			float m[4][4];

			inline Matrix4D(
				float _00 = 1, float _01 = 0, float _02 = 0, float _03 = 0,
				float _10 = 0, float _11 = 1, float _12 = 0, float _13 = 0,
				float _20 = 0, float _21 = 0, float _22 = 1, float _23 = 0,
			    float _30 = 0, float _31 = 0, float _32 = 0, float _33 = 1);

			inline Matrix4D(
				Vector4 r0,
				Vector4 r1,
				Vector4 r2,
				Vector4 r3);
		};

		inline Vector4 operator*(const Matrix4D& matrix, const Vector4& vector);

		inline Matrix4D operator*(const Matrix4D& left, const Matrix4D& right);

		inline Matrix4D transpose(const Matrix4D& in);

		inline Matrix4D perspectiveFovRH(float fovY, float ar, float zNear, float zFar);

		inline Matrix4D orthoRH(float left, float right, float bottom, float top, float zNear, float zFar);

		inline Matrix4D lookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up);

		inline float minor(float(&m)[4][4], int r0, int r1, int r2, int c0, int c1, int c2);

		inline void adjoint(float(&m)[4][4], float(&adjOut)[4][4]);

		inline float determinant(float(&m)[4][4]);

		inline bool inverse(float(&m)[4][4], float(&invOut)[4][4]);

		inline Matrix4D translate(float x, float y, float z);

		inline Matrix4D translate(const Vector3& vec);

		inline Matrix4D scale(float x, float y, float z);

		inline Matrix4D scale(const Vector3& vec);

		inline Matrix4D yaw(float angle);
		inline Matrix4D pitch(float angle);
		inline Matrix4D roll(float angle);

		inline Matrix4D rotate(float y, float p, float r);
		inline Matrix4D rotate(const Vector3& vec);

		inline Matrix4D rotateNormalAxis(float angle, const Vector3& u);

		inline Matrix4D rotateAxis(float angle, const Vector3& u);

#include "Voyager/Math/Matrix/Matrix4D.inl"
	}
}

#endif