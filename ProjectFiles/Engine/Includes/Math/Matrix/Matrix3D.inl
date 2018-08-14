
Matrix3D::Matrix3D(
	float _00, float _01, float _02,
	float _10, float _11, float _12,
	float _20, float _21, float _22) :
	m_00(_00), m_01(_01), m_02(_02),
	m_10(_10), m_11(_11), m_12(_12),
	m_20(_20), m_21(_21), m_22(_22)
{
}


Matrix3D Matrix3D::rotateZ(float radians)
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix3D(
		cos_val, -sin_val, 0,
		sin_val, cos_val, 0,
		0, 0, 1);
}

Matrix3D Matrix3D::translate(float x, float y)
{
	return Matrix3D(1, 0, x,
					0, 1, y,
					0, 0, 1);
}

Vector3D operator*(const Matrix3D& matrix, const Vector3D& vector)
{
	return Vector3D(
		matrix.m_00 * vector.x + matrix.m_01 * vector.y + matrix.m_02 * vector.z,
		matrix.m_10 * vector.x + matrix.m_11 * vector.y + matrix.m_12 * vector.z,
		matrix.m_20 * vector.x + matrix.m_21 * vector.y + matrix.m_22 * vector.z
	);
}

Matrix3D operator*(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(
		left.m_00 * right.m_00 + left.m_01 * right.m_10 + left.m_02 * right.m_20,
		left.m_00 * right.m_01 + left.m_01 * right.m_11 + left.m_02 * right.m_21,
		left.m_00 * right.m_02 + left.m_01 * right.m_12 + left.m_02 * right.m_22,

		left.m_10 * right.m_00 + left.m_11 * right.m_10 + left.m_12 * right.m_20,
		left.m_10 * right.m_01 + left.m_11 * right.m_11 + left.m_12 * right.m_21,
		left.m_10 * right.m_02 + left.m_11 * right.m_12 + left.m_12 * right.m_22,

		left.m_20 * right.m_00 + left.m_21 * right.m_10 + left.m_22 * right.m_20,
		left.m_20 * right.m_01 + left.m_21 * right.m_11 + left.m_22 * right.m_21,
		left.m_20 * right.m_02 + left.m_21 * right.m_12 + left.m_22 * right.m_22
	);
}
