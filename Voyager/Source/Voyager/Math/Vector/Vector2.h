#ifndef VE_MATH_VECTOR_2_H
#define VE_MATH_VECTOR_2_H

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/Descriptor.h"

namespace VE 
{
	namespace Math
	{
		struct Vector2 : public Vector::Base<2, Vector::DescXY>
		{
			inline Vector2(float xIn = 0.0f, float yIn = 0.0f)
			{
				x = xIn;
				y = yIn;
			}

			inline float dot(const Vector2& other) const;
			inline float magnitude() const;
			inline float magnitudeSquared() const;

			inline Vector2& operator += (const Vector2& right);
			inline Vector2& operator -= (const Vector2& right);
		};

		inline Vector2 operator-(const Vector2& left, const Vector2& right);

		inline Vector2 operator+(const Vector2& left, const Vector2& right);

		inline Vector2 operator*(float scalar, const Vector2& vector);

		inline Vector2 operator*(const Vector2& vector, float scalar);

#include "Voyager/Math/Vector/Vector2.inl"
	}
}

#endif
