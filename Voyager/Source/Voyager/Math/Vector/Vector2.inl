#include "Vector2.h"

Vector2::Vector2(const Vector::Base<Vector::LayoutXY>& other)
{
	x = other.x;
	y = other.y;
}