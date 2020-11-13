#ifndef VE_MATH_MATRIX_4x4_H
#define VE_MATH_MATRIX_4x4_H

#include "Voyager/Math/Matrix/Base.h"
#include "Voyager/Math/Matrix/MatrixLayout.h"

#include "Voyager/Math/Vector/Vector4.h"
#include "Voyager/Math/Vector/Vector3.h"
#include "Voyager/Math/Utils.h"

#include <algorithm>

namespace VE 
{
	namespace Math
	{
		struct Matrix4x4 : public Matrix::Base<Matrix::Layout4x4>
		{

			inline explicit Matrix4x4(
				float _00 = 1, float _01 = 0, float _02 = 0, float _03 = 0,
				float _10 = 0, float _11 = 1, float _12 = 0, float _13 = 0,
				float _20 = 0, float _21 = 0, float _22 = 1, float _23 = 0,
				float _30 = 0, float _31 = 0, float _32 = 0, float _33 = 1)
			{
				m[0][0] = _00;
				m[0][1] = _01;
				m[0][2] = _02;
				m[0][3] = _03;

				m[1][0] = _10;
				m[1][1] = _11;
				m[1][2] = _12;
				m[1][3] = _13;

				m[2][0] = _20;
				m[2][1] = _21;
				m[2][2] = _22;
				m[2][3] = _23;

				m[3][0] = _30;
				m[3][1] = _31;
				m[3][2] = _32;
				m[3][3] = _33;
			}

			inline Matrix4x4(const Matrix::Base<Matrix::Layout4x4>& other) 
			{
				m[0][0] = other.m[0][0];
			    m[0][1] = other.m[0][1];
			    m[0][2] = other.m[0][2];
			    m[0][3] = other.m[0][3];
			    
			    m[1][0] = other.m[1][0];
			    m[1][1] = other.m[1][1];
			    m[1][2] = other.m[1][2];
			    m[1][3] = other.m[1][3];
			    
			    m[2][0] = other.m[2][0];
			    m[2][1] = other.m[2][1];
			    m[2][2] = other.m[2][2];
			    m[2][3] = other.m[2][3];
			    
			    m[3][0] = other.m[3][0];
			    m[3][1] = other.m[3][1];
			    m[3][2] = other.m[3][2];
			    m[3][3] = other.m[3][3];
			}

			inline Matrix4x4(
				Vector4 r0,
				Vector4 r1,
				Vector4 r2,
				Vector4 r3);
		};

		inline Vector4 operator*(const Matrix4x4& matrix, const Vector4& vector);

		inline Matrix4x4 transpose(const Matrix4x4& in);

		inline Matrix4x4 perspectiveFovRH(float fovY, float ar, float zNear, float zFar);

		inline Matrix4x4 orthoRH(float left, float right, float bottom, float top, float zNear, float zFar);

		inline Matrix4x4 lookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up);

		inline float minor(float(&m)[4][4], int r0, int r1, int r2, int c0, int c1, int c2);

		inline void adjoint(float(&m)[4][4], float(&adjOut)[4][4]);

		inline float determinant(float(&m)[4][4]);

		inline bool inverse(float(&m)[4][4], float(&invOut)[4][4]);

		inline Matrix4x4 translate(float x, float y, float z);

		inline Matrix4x4 translate(const Vector3& vec);

		inline Matrix4x4 scale(float x, float y, float z);

		inline Matrix4x4 scale(const Vector3& vec);

		inline Matrix4x4 yaw(float angle);
		inline Matrix4x4 pitch(float angle);
		inline Matrix4x4 roll(float angle);

		inline Matrix4x4 rotate(float y, float p, float r);
		inline Matrix4x4 rotate(const Vector3& vec);

		inline Matrix4x4 rotateNormalAxis(float angle, const Vector3& u);

		inline Matrix4x4 rotateAxis(float angle, const Vector3& u);

#include "Voyager/Math/Matrix/Matrix4x4.inl"
	}
}

#endif