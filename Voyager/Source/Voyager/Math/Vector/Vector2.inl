
Vector2& Vector2::operator += (const Vector2& right)
{
	x += right.x;
	y += right.y;
	return *this;
}

Vector2& Vector2::operator -= (const Vector2& right)
{
	x -= right.x;
	y -= right.y;
	return *this;
}

Vector2 operator-(const Vector2& left, const Vector2& right)
{
	return Vector2(left.x - right.x, left.y - right.y);
}

Vector2 operator+(const Vector2& left, const Vector2& right)
{
	return Vector2(left.x + right.x, left.y + right.y);
}

Vector2 operator*(float scalar, const Vector2& vector)
{
	return Vector2(scalar * vector.x, scalar * vector.y);
}

Vector2 operator*(const Vector2& vector, float scalar)
{
	//return Vector2(vector.x * scalar, vector.y * scalar);
	return scalar * vector;
}