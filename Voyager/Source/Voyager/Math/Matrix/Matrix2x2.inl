
Matrix2x2 Matrix2x2::rotate(float radians) 
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix2x2(cos_val, -sin_val,
					sin_val, cos_val);
}

Vector2 operator*(
	const Matrix2x2& matrix,
	const Vector2& vector)
{
	return Vector2(matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y,
				   matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y);
}