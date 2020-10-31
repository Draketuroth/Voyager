#include "Vector3.h"

Vector3::Vector3(const Vector::Base<Vector::DescXYZ>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

Vector3 lerp(float alpha, const Vector3& source, const Vector3& target)
{
	return (1.0f - alpha) * source + alpha * target;
}