/*
* Matrix2DH.h
* Voyager Optimized 3D Matrix Class
*
*  Created on: Aug 15, 2018
*      Author: Fredrik Linde
*/

#ifndef VE_MATH_MATRIX_2DH_H
#define VE_MATH_MATRIX_2DH_H

#include <Math\Vector\Vector3D.h>

namespace Math
{
	// Row major
	struct Matrix2DH
	{
		float m_00;
		float m_01;
		float m_02;
		float m_10;
		float m_11;
		float m_12;
		Matrix2DH(
			float _00 = 1, float _01 = 0, float _02 = 0,
			float _10 = 0, float _11 = 1, float _12 = 0);
		inline static Matrix2DH rotateZ(float radians);
		inline static Matrix2DH translate(float x, float y);
	};

	inline Vector3D operator*(const Matrix2DH& matrix, const Vector3D& vector);
	inline Matrix2DH operator*(const Matrix2DH& left, const Matrix2DH& right);

#include "Matrix2DH.inl"
}

#endif