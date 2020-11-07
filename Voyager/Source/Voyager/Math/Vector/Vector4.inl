#include "Vector4.h"

Vector4::Vector4(const Vector::Base<Vector::LayoutXYZW>& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
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