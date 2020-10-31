#include "Vector2.h"

Vector2::Vector2(const Vector::Base<Vector::DescXY>& other)
{
	x = other.x;
	y = other.y;
}