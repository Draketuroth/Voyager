//============================================================================
// # VOYAGER ENGINE #
// Name			: Matrix2D.h
// Module		: Math
// Author		: Fredrik Linde
// Created on	: Aug 14, 2018
// Description	: Voyager 2D matrix class
//============================================================================

#ifndef VE_MATH_MATRIX_2D_H
#define VE_MATH_MATRIX_2D_H

#include <Math\Vector\Vector2D.h>
#include <cmath>

namespace Math
{
	// Struct - everything default public.
	struct Matrix2D
	{
		float m_00;
		float m_01;
		float m_10;
		float m_11;
		inline explicit Matrix2D(
			float _00 = 1, float _01 = 0,
			float _10 = 0, float _11 = 1);

		// Factory function - feed angle in radians and will yield a matrix 
		// that can be applied to a vector to perform a rotation.
		inline static Matrix2D rotate(float radians);
	};

	// The left hand is a matrix.
	inline Vector2D operator*(
		const Matrix2D& matrix,
		const Vector2D& vector);

#include "Matrix2D.inl"
}

#endif
