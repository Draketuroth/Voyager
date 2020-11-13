
Matrix2x2H Matrix2x2H::rotateZ(float radians)
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix2x2H(
		cos_val, -sin_val, 0,
		sin_val, cos_val, 0);
}

Matrix2x2H Matrix2x2H::translate(float x, float y)
{
	return Matrix2x2H(
		1, 0, x,
		0, 1, y);
}

Matrix2x2H Matrix2x2H::scale(float x, float y)
{
	return Matrix2x2H(
		x, 0, 0,
		0, y, 0);
}

Vector3 operator*(const Matrix2x2H& matrix, const Vector3& vector)
{
	return Vector3D(
		matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z,
		matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z,
		vector.z
	);
}

Matrix2x2H operator*(const Matrix2x2H& left, const Matrix2x2H& right)
{
	return Matrix2x2H(
		left.m[0][0] * right.m[0][0] + left.m[0][1] * right.m_10,
		left.m[0][0] * right.m[0][1] + left.m[0][1] * right.m_11,
		left.m[0][0] * right.m[0][2] + left.m[0][1] * right.m_12 + left.m_02,

		left.m[1][0] * right.m[0][0] + left.m_[1][1] * right.m[1][0],
		left.m[1][0] * right.m[0][1] + left.m_[1][1] * right.m[1][1],
		left.m[1][0] * right.m[0][2] + left.m_[1][1] * right.m[1][2] + left.m_12
	);
}
