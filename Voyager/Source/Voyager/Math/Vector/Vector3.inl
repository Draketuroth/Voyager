#include "Vector3.h"

Vector3::Vector3(const Vector::Base<Vector::DescXYZ>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3& Vector3::operator=(const Vector::Base<Vector::DescXYZ>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

Vector3& Vector3::operator+=(const Vector3& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

inline Vector3& Vector3::operator-=(const Vector3& right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	return *this;
}

Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

Vector3 operator+(const Vector3& left, const Vector3& right)
{
	return Vector3(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3 operator-(const Vector3& left, const Vector3& right)
{
	return Vector3(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3 operator*(float scalar, const Vector3& vector)
{
	return Vector3(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

Vector3 operator*(const Vector3& vector, float scalar)
{
	return scalar * vector;
}

Vector3 lerp(float alpha, const Vector3& source, const Vector3& target)
{
	return (1.0f - alpha) * source + alpha * target;
}