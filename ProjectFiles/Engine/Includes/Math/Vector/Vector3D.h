/*
* Vector3D.h
* Voyager 3D Vector Class
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#ifndef VE_MATH_VECTOR_3D_H
#define VE_MATH_VECTOR_3D_H

namespace Math
{
	struct Vector3D
	{
		float x;
		float y;
		float z;
		explicit Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
		inline Vector3D& operator+=(const Vector3D& right);
	};

	inline Vector3D operator+(const Vector3D& left, const Vector3D& right);
	inline Vector3D operator*(float scalar, const Vector3D& vector);
	inline Vector3D operator*(const Vector3D& vector, float scalar);

#include "Vector3D.inl"
}

#endif