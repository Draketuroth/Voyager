//============================================================================
// # VOYAGER ENGINE #
// Name			: Vector3D.h
// Module		: Math
// Author		: Fredrik Linde
// Created on	: Aug 14, 2018
// Description	: Voyager 3D vector class
//============================================================================

#ifndef VE_MATH_VECTOR_3D_H
#define VE_MATH_VECTOR_3D_H
#include <cmath>

namespace Math
{
	struct Vector3D
	{
		float x;
		float y;
		float z;
		explicit Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
		inline Vector3D& operator+=(const Vector3D& right);
		inline float dot(const Vector3D& other) const;
		inline float magnitude() const;
		inline float magnitudeSquared() const;
		inline Vector3D normalized() const;
		inline Vector3D perpCwXy() const;
		inline Vector3D perpCCwXy() const;
		inline Vector3D projectOnto(const Vector3D& target) const;
	};

	inline Vector3D operator+(const Vector3D& left, const Vector3D& right);
	inline Vector3D operator-(const Vector3D& left, const Vector3D& right);
	inline Vector3D operator*(float scalar, const Vector3D& vector);
	inline Vector3D operator*(const Vector3D& vector, float scalar);
	inline Vector3D lerp(float alpha, const Vector3D& source, const Vector3D& target);

#include "Vector3D.inl"
}

#endif