#ifndef VE_MATH_VECTOR_4D_H
#define VE_MATH_VECTOR_4D_H

namespace VE
{
	namespace Math
	{
		struct Vector4D
		{
			float x;
			float y;
			float z;
			float w;
			explicit Vector4D(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) : x(x), y(y), z(z), w(w) {}
			inline Vector4D& operator+=(const Vector4D& right);
			inline float dot(const Vector4D& other) const;
			inline float magnitude() const;
			inline float magnitudeSquared() const;
			inline Vector4D normalized() const;
		};

		inline Vector4D operator+(const Vector4D& left, const Vector4D& right);
		inline Vector4D operator-(const Vector4D& left, const Vector4D& right);
		inline Vector4D operator*(float scalar, const Vector4D& vector);
		inline Vector4D operator*(const Vector4D& vector, float scalar);

		inline Vector4D multiply(const Vector4D& a, const Vector4D& b);
		inline Vector4D multiplyAdd(const Vector4D& a, const Vector4D& b, const Vector4D& c);
		inline Vector4D negativeMultiplySubtract(const Vector4D& a, const Vector4D& b, const Vector4D& c);

		inline Vector4D splatX(const Vector4D& in);
		inline Vector4D splatY(const Vector4D& in);
		inline Vector4D splatZ(const Vector4D& in);
		inline Vector4D mergeXY(const Vector4D& a, const Vector4D& b);
		inline Vector4D mergeZW(const Vector4D& a, const Vector4D& b);
		inline Vector4D lerp(float alpha, const Vector4D& source, const Vector4D& target);

#include "Voyager/Math/Vector/Vector4D.inl"
	}
}

#endif