#ifndef VE_MATH_VECTOR_4_H
#define VE_MATH_VECTOR_4_H

#include "Voyager/Math/Vector/Base.h"
#include "Voyager/Math/Vector/Descriptor.h"

namespace VE
{
	namespace Math
	{
		struct Vector4 : public Vector::Base<Vector::DescXYZW>
		{
			inline Vector4(float xIn = 0.0f, float yIn = 0.0f, float zIn = 0.0f, float wIn = 1.0f) 
			{
				x = xIn;
				y = yIn;
				z = zIn;
				w = wIn;
			}

			inline Vector4(const Vector::Base<Vector::DescXYZW>& other);

			inline Vector4& operator=(const Vector::Base<Vector::DescXYZW>& other);
			inline Vector4& operator+=(const Vector4& right);
		};

		inline Vector4 operator+(const Vector4& left, const Vector4& right);
		inline Vector4 operator-(const Vector4& left, const Vector4& right);
		inline Vector4 operator*(float scalar, const Vector4& vector);
		inline Vector4 operator*(const Vector4& vector, float scalar);

		inline Vector4 multiply(const Vector4& a, const Vector4& b);
		inline Vector4 multiplyAdd(const Vector4& a, const Vector4& b, const Vector4& c);
		inline Vector4 negativeMultiplySubtract(const Vector4& a, const Vector4& b, const Vector4& c);

		inline Vector4 splatX(const Vector4& in);
		inline Vector4 splatY(const Vector4& in);
		inline Vector4 splatZ(const Vector4& in);
		inline Vector4 mergeXY(const Vector4& a, const Vector4& b);
		inline Vector4 mergeZW(const Vector4& a, const Vector4& b);
		inline Vector4 lerp(float alpha, const Vector4& source, const Vector4& target);

#include "Voyager/Math/Vector/Vector4.inl"
	}
}

#endif