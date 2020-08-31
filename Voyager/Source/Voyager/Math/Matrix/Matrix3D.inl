
Matrix3D::Matrix3D(
	float _00, float _01, float _02,
	float _10, float _11, float _12,
	float _20, float _21, float _22)
{
	m[0][0] = _00;
	m[0][1] = _01;
	m[0][2] = _02;

	m[1][0] = _10;
	m[1][1] = _11;
	m[1][2] = _12;

	m[2][0] = _20;
	m[2][1] = _21;
	m[2][2] = _22;
}

Matrix3D::Matrix3D(float(&mat)[4][4]) 
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
	return Matrix3D(
		1, 0, x,
		0, 1, y,
		0, 0, 1);
}

Matrix3D Matrix3D::scale(float x, float y)
{
	return Matrix3D(
		x, 0, 0,
		0, y, 0,
		0, 0, 1);
}

Vector3D operator*(const Vector3D& vector, const Matrix3D& matrix)
{
	return Vector3D(
		vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0],
		vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1],
		vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2]
	);
}

Matrix3D operator*(const Matrix3D& left, const Matrix3D& right)
{
	return Matrix3D(
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
