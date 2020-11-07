#include "Vector3.h"

Vector3::Vector3(const Vector::Base<Vector::LayoutXYZ>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}