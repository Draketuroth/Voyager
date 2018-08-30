//============================================================================
// # VOYAGER ENGINE #
// Name: Matrix3D.h
// Module: Math
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Voyager 3D matrix class
//============================================================================

#ifndef VE_MATH_MATRIX_3D_H
#define VE_MATH_MATRIX_3D_H

#include <Math\Vector\Vector3D.h>

namespace Math
{
	// Row major
	struct Matrix3D
	{
		float m_00;
		float m_01;
		float m_02;
		float m_10;
		float m_11;
		float m_12;
		float m_20;
		float m_21;
		float m_22;
		Matrix3D(
			float _00 = 1, float _01 = 0, float _02 = 0,
			float _10 = 0, float _11 = 1, float _12 = 0,
			float _20 = 0, float _21 = 0, float _22 = 1);
		inline static Matrix3D rotateZ(float radians);
		inline static Matrix3D translate(float x, float y);
		inline static Matrix3D scale(float x, float y);
	};

	inline Vector3D operator*(const Matrix3D& matrix, const Vector3D& vector);
	inline Matrix3D operator*(const Matrix3D& left, const Matrix3D& right);

#include "Matrix3D.inl"
}

#endif