#ifndef VE_MATH_VECTOR_3D_H
#define VE_MATH_VECTOR_3D_H
#include <cmath>

namespace VE 
{
	namespace Math
	{
		struct Vector3D
		{
			float x;
			float y;
			float z;
			explicit Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
			inline Vector3D& operator+=(const Vector3D& right);
			inline Vector3D& operator-=(const Vector3D& right);
			inline float dot(const Vector3D& other) const;
			inline float magnitude() const;
			inline float magnitudeSquared() const;
			inline Vector3D normalized() const;
		};

		inline float dot(const Vector3D& a, const Vector3D& b);
		inline Vector3D normalize(const Vector3D& vector);
		inline Vector3D cross(const Vector3D& a, const Vector3D& b);

		inline Vector3D operator+(const Vector3D& left, const Vector3D& right);
		inline Vector3D operator-(const Vector3D& left, const Vector3D& right);
		inline Vector3D operator*(float scalar, const Vector3D& vector);
		inline Vector3D operator*(const Vector3D& vector, float scalar);
		inline Vector3D lerp(float alpha, const Vector3D& source, const Vector3D& target);

#include "Voyager/Math/Vector/Vector3D.inl"
	}
}

#endif