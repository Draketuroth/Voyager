#include "Vector4.h"

Vector4::Vector4(const Vector::Base<Vector::DescXYZW>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

Vector4& Vector4::operator=(const Vector::Base<Vector::DescXYZW>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}

Vector4& Vector4::operator+=(const Vector4& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

Vector4 operator+(const Vector4& left, const Vector4& right)
{
	return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, 1.0f);
}

Vector4 operator-(const Vector4& left, const Vector4& right)
{
	return Vector4(left.x - right.x, left.y - right.y, left.z - right.z, 1.0f);
}

Vector4 operator*(float scalar, const Vector4& vector)
{
	return Vector4(scalar * vector.x, scalar * vector.y, scalar * vector.z, 1.0f);
}

Vector4 operator*(const Vector4& vector, float scalar)
{
	return scalar * vector;
}

Vector4 multiply(const Vector4& a, const Vector4& b) 
{
	return Vector4(a.x * b.x,
					a.y * b.y,
					a.z * b.z,
					a.w * b.w);
}

Vector4 multiplyAdd(const Vector4& a, const Vector4& b, const Vector4& c) 
{
	return Vector4(a.x * b.x + c.x,
					a.y * b.y + c.y,
					a.z * b.z + c.z,
					a.w * b.w + c.w);
}

Vector4 negativeMultiplySubtract(const Vector4& a, const Vector4& b, const Vector4& c) 
{
	return Vector4(c.x - a.x * b.x,
					c.y - a.y * b.y,
					c.z - a.z * b.z,
					c.w - a.w * b.w);
}

Vector4 splatX(const Vector4& in)
{
	return Vector4(in.x, in.x, in.x, in.x);
}

Vector4 splatY(const Vector4& in)
{
	return Vector4(in.y, in.y, in.y, in.y);
}

Vector4 splatZ(const Vector4& in)
{
	return Vector4(in.z, in.z, in.z, in.z);
}

Vector4 mergeXY(const Vector4& a, const Vector4& b)
{
	Vector4 out;

	out.x = a.x;
	out.y = b.x;
	out.z = a.y;
	out.w = b.y;

	return out;
}

Vector4 mergeZW(const Vector4& a, const Vector4& b)
{
	Vector4 out;

	out.x = a.z;
	out.y = b.z;
	out.z = a.w;
	out.w = b.w;

	return out;
}

Vector4 lerp(float alpha, const Vector4& source, const Vector4& target)
{
	return (1.0f - alpha) * source + alpha * target;
}