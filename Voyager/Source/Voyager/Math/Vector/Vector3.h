#ifndef VE_MATH_VECTOR_3_H
#define VE_MATH_VECTOR_3_H
#include <cmath>

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/Descriptor.h"

namespace VE 
{
	namespace Math
	{
		struct Vector3 : public Vector::Base<3, Vector::DescXYZ>
		{
			inline Vector3(float xIn = 0.0, float yIn = 0.0, float zIn = 0.0) 
			{
				x = xIn;
				y = yIn;
				z = zIn;
			}
			inline Vector3& operator+=(const Vector3& right);
			inline Vector3& operator-=(const Vector3& right);
			inline float dot(const Vector3& other) const;
			inline float magnitude() const;
			inline float magnitudeSquared() const;
			inline Vector3 normalized() const;
		};

		inline float dot(const Vector3& a, const Vector3& b);
		inline Vector3 normalize(const Vector3& vector);
		inline Vector3 cross(const Vector3& a, const Vector3& b);

		inline Vector3 operator+(const Vector3& left, const Vector3& right);
		inline Vector3 operator-(const Vector3& left, const Vector3& right);
		inline Vector3 operator*(float scalar, const Vector3& vector);
		inline Vector3 operator*(const Vector3& vector, float scalar);
		inline Vector3 lerp(float alpha, const Vector3& source, const Vector3& target);

#include "Voyager/Math/Vector/Vector3.inl"
	}
}

#endif