
Matrix3x3::Matrix3x3(float(&mat)[4][4]) 
{
	m[0][0] = mat[0][0];
	m[0][1] = mat[0][1];
	m[0][2] = mat[0][2];

	m[1][0] = mat[1][0];
	m[1][1] = mat[1][1];
	m[1][2] = mat[1][2];

	m[2][0] = mat[2][0];
	m[2][1] = mat[2][1];
	m[2][2] = mat[2][2];
}

Matrix3x3 Matrix3x3::rotateZ(float radians)
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix3x3(
		cos_val, -sin_val, 0,
		sin_val, cos_val, 0,
		0, 0, 1);
}

Matrix3x3 Matrix3x3::translate(float x, float y)
{
	return Matrix3x3(
		1, 0, x,
		0, 1, y,
		0, 0, 1);
}

Matrix3x3 Matrix3x3::scale(float x, float y)
{
	return Matrix3x3(
		x, 0, 0,
		0, y, 0,
		0, 0, 1);
}

Vector3 operator*(const Vector3& vector, const Matrix3x3& matrix)
{
	return Vector3(
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1],
		vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2]
	);
}

Matrix3x3 operator*(const Matrix3x3& left, const Matrix3x3& right)
{
	return Matrix3x3(
		left.m[0][0] * right.m[0][0] + left.m[0][1] * right.m[1][0] + left.m[0][2] * right.m[2][0],
		left.m[0][0] * right.m[0][1] + left.m[0][1] * right.m[1][1] + left.m[0][2] * right.m[2][1],
		left.m[0][0] * right.m[0][2] + left.m[0][1] * right.m[1][2] + left.m[0][2] * right.m[2][2],

		left.m[1][0] * right.m[0][0] + left.m[1][1] * right.m[1][0] + left.m[1][2] * right.m[2][0],
		left.m[1][0] * right.m[0][1] + left.m[1][1] * right.m[1][1] + left.m[1][2] * right.m[2][1],
		left.m[1][0] * right.m[0][2] + left.m[1][1] * right.m[1][2] + left.m[1][2] * right.m[2][2],

		left.m[2][0] * right.m[0][0] + left.m[2][1] * right.m[1][0] + left.m[2][2] * right.m[2][0],
		left.m[2][0] * right.m[0][1] + left.m[2][1] * right.m[1][1] + left.m[2][2] * right.m[2][1],
		left.m[2][0] * right.m[0][2] + left.m[2][1] * right.m[1][2] + left.m[2][2] * right.m[2][2]
	);
}
