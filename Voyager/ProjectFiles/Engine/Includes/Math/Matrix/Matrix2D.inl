
Matrix2D::Matrix2D(
	float _00, float _01,
	float _10, float _11) :
	m_00(_00), m_01(_01),
	m_10(_10), m_11(_11)
{

}

Matrix2D Matrix2D::rotate(float radians) 
{
	float cos_val = cos(radians);
	float sin_val = sin(radians);
	return Matrix2D(cos_val, -sin_val,
					sin_val, cos_val);
}

Vector2D operator*(
	const Matrix2D& matrix,
	const Vector2D& vector)
{
	return Vector2D(matrix.m_00 * vector.x + matrix.m_01 * vector.y,
					matrix.m_10 * vector.x + matrix.m_11 * vector.y);
}