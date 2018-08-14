/*
* Vector2D.h
* Voyager 2D Vector Class
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#ifndef VE_MATH_VECTOR_2D_H
#define VE_MATH_VECTOR_2D_H

namespace Math
{
	struct Vector2D
	{
		float x;
		float y;

		// Make it explicit to prevent automatic conversion.
		// If we are going to convert something, it must be explicit via cast.
		explicit Vector2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}
		inline Vector2D& operator += (const Vector2D& right);
		inline Vector2D& operator -= (const Vector2D& right);
	};

	inline Vector2D operator+(const Vector2D& left, const Vector2D& right);

	inline Vector2D operator*(float scalar, const Vector2D& vector);

	inline Vector2D operator*(const Vector2D& vector, float scalar);

#include "Vector2D.inl"
}

#endif
