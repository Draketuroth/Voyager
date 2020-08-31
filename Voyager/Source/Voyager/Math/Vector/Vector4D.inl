
Vector4D& Vector4D::operator+=(const Vector4D& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

float Vector4D::dot(const Vector4D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector4D::magnitude() const
{
	return sqrt(magnitudeSquared());
	// return sqrt(x * x + y * y + z * z);
}

float Vector4D::magnitudeSquared() const
{
	return this->dot(*this);
}

Vector4D Vector4D::normalized() const
{
	float inverseMagnitude = 1.0f / magnitude();
	return inverseMagnitude * (*this);
}

Vector4D operator+(const Vector4D& left, const Vector4D& right)
{
	return Vector4D(left.x + right.x, left.y + right.y, left.z + right.z, 1.0f);
}

Vector4D operator-(const Vector4D& left, const Vector4D& right)
{
	return Vector4D(left.x - right.x, left.y - right.y, left.z - right.z, 1.0f);
}

Vector4D operator*(float scalar, const Vector4D& vector)
{
	return Vector4D(scalar * vector.x, scalar * vector.y, scalar * vector.z, 1.0f);
}

Vector4D operator*(const Vector4D& vector, float scalar)
{
	return scalar * vector;
}

Vector4D multiply(const Vector4D& a, const Vector4D& b) 
{
	return Vector4D(a.x * b.x,
					a.y * b.y,
					a.z * b.z,
					a.w * b.w);
}

Vector4D multiplyAdd(const Vector4D& a, const Vector4D& b, const Vector4D& c) 
{
	return Vector4D(a.x * b.x + c.x,
					a.y * b.y + c.y,
					a.z * b.z + c.z,
					a.w * b.w + c.w);
}

Vector4D negativeMultiplySubtract(const Vector4D& a, const Vector4D& b, const Vector4D& c) 
{
	return Vector4D(c.x - a.x * b.x,
					c.y - a.y * b.y,
					c.z - a.z * b.z,
					c.w - a.w * b.w);
}

Vector4D splatX(const Vector4D& in)
{
	return Vector4D(in.x, in.x, in.x, in.x);
}

Vector4D splatY(const Vector4D& in)
{
	return Vector4D(in.y, in.y, in.y, in.y);
}

Vector4D splatZ(const Vector4D& in)
{
	return Vector4D(in.z, in.z, in.z, in.z);
}

Vector4D mergeXY(const Vector4D& a, const Vector4D& b)
{
	Vector4D out;

	out.x = a.x;
	out.y = b.x;
	out.z = a.y;
	out.w = b.y;

	return out;
}

Vector4D mergeZW(const Vector4D& a, const Vector4D& b)
{
	Vector4D out;

	out.x = a.z;
	out.y = b.z;
	out.z = a.w;
	out.w = b.w;

	return out;
}

Vector4D lerp(float alpha, const Vector4D& source, const Vector4D& target)
{
	return (1.0f - alpha) * source + alpha * target;
}