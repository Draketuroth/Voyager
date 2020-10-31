#ifndef VE_MATH_VECTOR_2_H
#define VE_MATH_VECTOR_2_H

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/Descriptor.h"

namespace VE 
{
	namespace Math
	{
		struct Vector2 : public Vector::Base<Vector::DescXY>
		{
			inline Vector2(float xIn = 0.0f, float yIn = 0.0f)
			{
				x = xIn;
				y = yIn;
			}

			inline Vector2(const Vector::Base<Vector::DescXY>& other);

			inline Vector2& operator=(const Vector::Base<Vector::DescXY>& other);
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