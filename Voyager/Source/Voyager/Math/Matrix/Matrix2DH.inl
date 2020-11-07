
Matrix2DH::Matrix2DH(
	float _00, float _01, float _02,
	float _10, float _11, float _12)
{
	m[0][0] = _00;
	m[0][1] = _01;
	m[0][2] = _02;

	m[1][0] = _10;
	m[1][1] = _11;
	m[1][2] = _12;
}


Matrix2DH Matrix2DH::rotateZ(float radians)
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix2DH(
		cos_val, -sin_val, 0,
		sin_val, cos_val, 0);
}

Matrix2DH Matrix2DH::translate(float x, float y)
{
	return Matrix2DH(
		1, 0, x,
		0, 1, y);
}

Matrix2DH Matrix2DH::scale(float x, float y)
{
	return Matrix2DH(
		x, 0, 0,
		0, y, 0);
}

Vector3 operator*(const Matrix2DH& matrix, const Vector3& vector)
{
	return Vector3D(
		matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z,
		matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z,
		vector.z
	);
}

Matrix2DH operator*(const Matrix2DH& left, const Matrix2DH& right)
{
	return Matrix2DH(
		left.m[0][0] * right.m[0][0] + left.m[0][1] * right.m_10,
		left.m[0][0] * right.m[0][1] + left.m[0][1] * right.m_11,
		left.m[0][0] * right.m[0][2] + left.m[0][1] * right.m_12 + left.m_02,

		left.m[1][0] * right.m[0][0] + left.m_[1][1] * right.m[1][0],
		left.m[1][0] * right.m[0][1] + left.m_[1][1] * right.m[1][1],
		left.m[1][0] * right.m[0][2] + left.m_[1][1] * right.m[1][2] + left.m_12
	);
}
