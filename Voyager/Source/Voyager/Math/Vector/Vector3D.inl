
Vector3D& Vector3D::operator+=(const Vector3D& right)
{
	this->x += right.x;
	this->y += right.y;
	this->z += right.z;
	return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& right)
{
	this->x -= right.x;
	this->y -= right.y;
	this->z -= right.z;
	return *this;
}

float Vector3D::dot(const Vector3D& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

float Vector3D::magnitude() const
{
	return sqrt(magnitudeSquared());
	// return sqrt(x * x + y * y + z * z);
}

float Vector3D::magnitudeSquared() const
{
	return this->dot(*this);
}

Vector3D Vector3D::normalized() const
{
	float inverseMagnitude = 1.0f / magnitude();
	return inverseMagnitude * (*this);
}

float dot(const Vector3D& a, const Vector3D& b) 
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3D normalize(const Vector3D& vector)
{
	float l = vector.magnitude();
	return Vector3D(vector.x / l, vector.y / l, vector.z / l);
}

Vector3D cross(const Vector3D& a, const Vector3D& b)
{
	return Vector3D((a.y * b.z - a.z * b.y), (a.z * b.x - a.x * b.z), (a.x * b.y - a.y * b.x));
}

Vector3D operator+(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3D operator-(const Vector3D& left, const Vector3D& right)
{
	return Vector3D(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3D operator*(float scalar, const Vector3D& vector)
{
	return Vector3D(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

Vector3D operator*(const Vector3D& vector, float scalar)
{
	return scalar * vector;
}

Vector3D lerp(float alpha, const Vector3D& source, const Vector3D& target)
{
	return (1.0f - alpha) * source + alpha * target;
}