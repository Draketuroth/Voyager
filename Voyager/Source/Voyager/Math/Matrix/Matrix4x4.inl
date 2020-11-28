#include "Matrix4x4.h"

Matrix4x4::Matrix4x4(
	Vector4 r0,
	Vector4 r1,
	Vector4 r2,
	Vector4 r3)
{
	m[0][0] = r0.x;
	m[0][1] = r0.y;
	m[0][2] = r0.z;
	m[0][3] = r0.w;

	m[1][0] = r1.x;
	m[1][1] = r1.y;
	m[1][2] = r1.z;
	m[1][3] = r1.w;

	m[2][0] = r2.x;
	m[2][1] = r2.y;
	m[2][2] = r2.z;
	m[2][3] = r2.w;

	m[3][0] = r3.x;
	m[3][1] = r3.y;
	m[3][2] = r3.z;
	m[3][3] = r3.w;
}

Vector4 operator*(const Matrix4x4& matrix, const Vector4& vector)
{
	return Vector4(
		matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y + matrix.m[0][2] * vector.z + matrix.m[0][3] * vector.w,
		matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y + matrix.m[1][2] * vector.z + matrix.m[1][3] * vector.w,
		matrix.m[2][0] * vector.x + matrix.m[2][1] * vector.y + matrix.m[2][2] * vector.z + matrix.m[2][3] * vector.w,
		matrix.m[3][0] * vector.x + matrix.m[3][1] * vector.y + matrix.m[3][2] * vector.z + matrix.m[3][3] * vector.w
	);
}

Matrix4x4 transpose(const Matrix4x4& in) 
{
	Vector4 M0, M1, M2, M3;
	M0 = Vector4(in.m[0][0], in.m[0][1], in.m[0][2], in.m[0][3]);
	M1 = Vector4(in.m[1][0], in.m[1][1], in.m[1][2], in.m[1][3]);
	M2 = Vector4(in.m[2][0], in.m[2][1], in.m[2][2], in.m[2][3]);
	M3 = Vector4(in.m[3][0], in.m[3][1], in.m[3][2], in.m[3][3]);

	Vector4 P0, P1, P2, P3;
	P0 = mergeXY(M0, M2); // m00m20m01m21
	P1 = mergeXY(M1, M3); // m10m30m11m31
	P2 = mergeZW(M0, M2); // m02m22m03m23
	P3 = mergeZW(M1, M3); // m12m32m13m33

	Vector4 T0, T1, T2, T3;
	T0 = mergeXY(P0, P1); // m00m10m20m30
	T1 = mergeZW(P0, P1); // m01m11m21m31
	T2 = mergeXY(P2, P3); // m02m12m22m32
	T3 = mergeZW(P2, P3); // m03m13m23m33

	return Matrix4x4(T0, T1, T2, T3);
}

Matrix4x4 perspectiveFovRH(float fovY, float ar, float zNear, float zFar) 
{
	float rad = fovY;
	float h = cos(0.5f * rad) / sin(0.5 * rad);
	float w = h * 1.0f;

	Matrix4x4 persp;
	persp.m[0][0] = w;
	persp.m[1][1] = h;
	persp.m[2][2] = -(zFar + zNear) / (zFar - zNear);
	persp.m[2][3] = -1.0f;
	persp.m[3][2] = -(2.0f * zFar * zNear) / (zFar - zNear);

	return persp;
}

Matrix4x4 orthoRH(float left, float right, float bottom, float top, float zNear, float zFar)
{
	float ReciprocalWidth = 1.0f / (right - left);
	float ReciprocalHeight = 1.0f / (top - bottom);
	float fRange = 1.0f / (zNear - zFar);

	return Matrix4x4(
		ReciprocalWidth + ReciprocalWidth, 0.0f, 0.0f, 0.0f,
		0.0f, ReciprocalHeight + ReciprocalHeight, 0.0f, 0.0f,
		0.0f, 0.0f, fRange, 0.0f,
		-(left + right) * ReciprocalWidth, -(top + bottom) * ReciprocalHeight, fRange * zNear, 1.0f);
}

Matrix4x4 lookAtRH(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 zaxis = normalize(eye - at);
	Vector3 xaxis = normalize(cross(up, zaxis));
	Vector3 yaxis = cross(zaxis, xaxis);

	Matrix4x4 lookAtMatrix;

	lookAtMatrix.m[0][0] = xaxis.x;
	lookAtMatrix.m[0][1] = yaxis.x;
	lookAtMatrix.m[0][2] = zaxis.x;

	lookAtMatrix.m[1][0] = xaxis.y;
	lookAtMatrix.m[1][1] = yaxis.y;
	lookAtMatrix.m[1][2] = zaxis.y;

	lookAtMatrix.m[2][0] = xaxis.z;
	lookAtMatrix.m[2][1] = yaxis.z;
	lookAtMatrix.m[2][2] = zaxis.z;

	Vector3 negEye = Vector3(-eye.x, -eye.y, -eye.z);

	lookAtMatrix.m[3][0] = dot(xaxis, negEye);
	lookAtMatrix.m[3][1] = dot(yaxis, negEye);
	lookAtMatrix.m[3][2] = dot(zaxis, negEye);

	lookAtMatrix.m[3][3] = 1.0f;

	return lookAtMatrix;
}

float minor(float(&m)[4][4], int r0, int r1, int r2, int c0, int c1, int c2)
{
	return m[r0][c0] * (m[r1][c1] * m[r2][c2] - m[r2][c1] * m[r1][c2]) -
		   m[r0][c1] * (m[r1][c0] * m[r2][c2] - m[r2][c0] * m[r1][c2]) +
		   m[r0][c2] * (m[r1][c0] * m[r2][c1] - m[r2][c0] * m[r1][c1]);
}

void adjoint(float(&m)[4][4], float(&adjOut)[4][4])
{
	adjOut[0][0] = minor(m, 1, 2, 3, 1, 2, 3);
	adjOut[0][1] = -minor(m, 0, 2, 3, 1, 2, 3);
	adjOut[0][2] = minor(m, 0, 1, 3, 1, 2, 3);
	adjOut[0][3] = -minor(m, 0, 1, 2, 1, 2, 3);

	adjOut[1][0] = -minor(m, 1, 2, 3, 0, 2, 3);
	adjOut[1][1] = minor(m, 0, 2, 3, 0, 2, 3);
	adjOut[1][2] = -minor(m, 0, 1, 3, 0, 2, 3);
	adjOut[1][3] = minor(m, 0, 1, 2, 0, 2, 3);

	adjOut[2][0] = minor(m, 1, 2, 3, 0, 1, 3);
	adjOut[2][1] = -minor(m, 0, 2, 3, 0, 1, 3);
	adjOut[2][2] = minor(m, 0, 1, 3, 0, 1, 3);
	adjOut[2][3] = -minor(m, 0, 1, 2, 0, 1, 3);

	adjOut[3][0] = -minor(m, 1, 2, 3, 0, 1, 2);
	adjOut[3][1] = minor(m, 0, 2, 3, 0, 1, 2);
	adjOut[3][2] = -minor(m, 0, 1, 3, 0, 1, 2);
	adjOut[3][3] = minor(m, 0, 1, 2, 0, 1, 2);
}

float determinant(float(&m)[4][4])
{
	return m[0][0] * minor(m, 1, 2, 3, 1, 2, 3) -
		   m[0][1] * minor(m, 1, 2, 3, 0, 2, 3) +
		   m[0][2] * minor(m, 1, 2, 3, 0, 1, 3) -
		   m[0][3] * minor(m, 1, 2, 3, 0, 1, 2);
}

bool inverse(float(&m)[4][4], float(&invOut)[4][4]) 
{
	adjoint(m, invOut);

	float det = determinant(m);
	if (det == 0.0f) { return false; }

	float inv_det = 1.0f / det;
	for (int r = 0; r < 4; r++)
	{
		for (int c = 0; c < 4; c++)
		{
			invOut[r][c] = invOut[r][c] * inv_det;
		}
	}
	return true;
}

Matrix4x4 translate(float x, float y, float z)
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 1.0f);
}

Matrix4x4 translate(const Vector3& vec)
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		vec.x, vec.y, vec.z, 1.0f);
}

Matrix4x4 scale(float x, float y, float z)
{
	return Matrix4x4(
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 scale(const Vector3& vec)
{
	return Matrix4x4(
		vec.x, 0.0f, 0.0f, 0.0f,
		0.0f, vec.y, 0.0f, 0.0f,
		0.0f, 0.0f, vec.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 roll(float angle) 
{
	float a = toRadians(angle);
	float c = cos(a);
	float s = sin(a);
	return Matrix4x4(
		c, -s, 0.0f, 0.0f,
		s, c, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 yaw(float angle) 
{
	float a = toRadians(angle);
	float c = cos(a);
	float s = sin(a);
	return Matrix4x4(
		c, 0.0f, s, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-s, 0.0f, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 pitch(float angle) 
{
	float a = toRadians(angle);
	float c = cos(a);
	float s = sin(a);
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c, -s, 0.0f,
		0.0f, s, c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 rotate(float y, float p, float r) 
{
	return roll(r) * pitch(p) * yaw(y);
}

Matrix4x4 rotate(const Vector3& vec)
{
	return roll(vec.x) * pitch(vec.y) * yaw(vec.z);
}

Matrix4x4 rotateNormalAxis(float angle, const Vector3& u)
{
	float fSinAngle = sin(angle);
	float fCosAngle = cos(angle);

	Vector4 NormalAxis = Vector4(u.x, u.y, u.z, 1.0f);

	Vector4 A = Vector4(fSinAngle, fCosAngle, 1.0f - fCosAngle, 0.0f);

	Vector4 C2 = splatZ(A);
	Vector4 C1 = splatY(A);
	Vector4 C0 = splatX(A);

	Vector4 N0 = Vector4(NormalAxis.y, NormalAxis.z, NormalAxis.x, NormalAxis.w);
	Vector4 N1 = Vector4(NormalAxis.z, NormalAxis.x, NormalAxis.y, NormalAxis.w);

	Vector4 V0 = multiply(C2, N0);
	V0 = multiply(V0, N1);

	Vector4 R0 = multiply(C2, NormalAxis);
	R0 = multiplyAdd(R0, NormalAxis, C1);

	Vector4 R1 = multiplyAdd(C0, NormalAxis, V0);
	Vector4 R2 = negativeMultiplySubtract(C0, NormalAxis, V0);

	V0 = Vector4(R0.x, R0.y, R0.z, A.w);

	Vector4 V1 = Vector4(R1.z, R2.y, R2.z, R1.x);

	Vector4 V2 = Vector4(R1.y, R2.x, R1.y, R2.x);

	Vector4 F0, F1, F2, F3;
	F0 = Vector4(V0.x, V1.x, V1.y, V0.w);
	F1 = Vector4(V1.z, V0.y, V1.w, V0.w);
	F2 = Vector4(V2.x, V2.y, V0.z, V0.w);
	F3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

	return Matrix4x4(F0, F1, F2, F3);
}

Matrix4x4 rotateAxis(float angle, const Vector3& u) 
{
	Vector3 normal = normalize(u);
	return rotateNormalAxis(angle, normal);
}