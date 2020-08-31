#ifndef VE_MATH_VECTOR_2D_H
#define VE_MATH_VECTOR_2D_H

namespace VE 
{
	namespace Math
	{
		struct Vector2D
		{
			float x;
			float y;

			// Make it explicit to prevent automatic conversion.
			// If we are going to convert something, it must be explicit via cast.
			explicit Vector2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

			inline float dot(const Vector2D& other) const;
			inline float magnitude() const;
			inline float magnitudeSquared() const;

			inline Vector2D& operator += (const Vector2D& right);
			inline Vector2D& operator -= (const Vector2D& right);
		};

		inline Vector2D operator-(const Vector2D& left, const Vector2D& right);

		inline Vector2D operator+(const Vector2D& left, const Vector2D& right);

		inline Vector2D operator*(float scalar, const Vector2D& vector);

		inline Vector2D operator*(const Vector2D& vector, float scalar);

#include "Voyager/Math/Vector/Vector2D.inl"
	}
}

#endif
