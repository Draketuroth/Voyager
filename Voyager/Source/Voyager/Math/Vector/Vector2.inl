
float Vector2::dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}
float Vector2::magnitude() const
{
	return sqrt(magnitudeSquared());
	// return sqrt(x * x + y * y + z * z);
}
float Vector2::magnitudeSquared() const
{
	return this->dot(*this);
}

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