
Matrix2D::Matrix2D(
	float _00, float _01,
	float _10, float _11)
{
	m[0][0] = _00;
	m[0][1] = _01;

	m[1][0] = _10;
	m[1][1] = _11;
}

Matrix2D Matrix2D::rotate(float radians) 
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix2D(cos_val, -sin_val,
					sin_val, cos_val);
}

Vector2 operator*(
	const Matrix2D& matrix,
	const Vector2& vector)
{
	return Vector2(matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y,
				   matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y);
}