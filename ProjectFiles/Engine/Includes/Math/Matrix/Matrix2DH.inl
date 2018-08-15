
Matrix2DH::Matrix2DH(
	float _00, float _01, float _02,
	float _10, float _11, float _12) :
	m_00(_00), m_01(_01), m_02(_02),
	m_10(_10), m_11(_11), m_12(_12)
{
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

Vector3D operator*(const Matrix2DH& matrix, const Vector3D& vector)
{
	return Vector3D(
		matrix.m_00 * vector.x + matrix.m_01 * vector.y + matrix.m_02 * vector.z,
		matrix.m_10 * vector.x + matrix.m_11 * vector.y + matrix.m_12 * vector.z,
		vector.z
	);
}

Matrix2DH operator*(const Matrix2DH& left, const Matrix2DH& right)
{
	return Matrix2DH(
		left.m_00 * right.m_00 + left.m_01 * right.m_10,
		left.m_00 * right.m_01 + left.m_01 * right.m_11,
		left.m_00 * right.m_02 + left.m_01 * right.m_12 + left.m_02,

		left.m_10 * right.m_00 + left.m_11 * right.m_10,
		left.m_10 * right.m_01 + left.m_11 * right.m_11,
		left.m_10 * right.m_02 + left.m_11 * right.m_12 + left.m_12
	);
}
