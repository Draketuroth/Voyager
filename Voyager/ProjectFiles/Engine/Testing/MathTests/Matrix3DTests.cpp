
#include <gtest\gtest.h>
#include <Math\Matrix\Matrix3D.h>
#include <Math\Vector\Vector3D.h>
#include <Math\Constants.h>
#include "Testing\TestingHelper.h"

using Math::Matrix3D;
using Math::Vector3D;

TEST(Matrix3D, Construction)
{
	Matrix3D identity;
	EXPECT_FLOAT_EQ(identity.m_00, 1);
	EXPECT_FLOAT_EQ(identity.m_01, 0);
	EXPECT_FLOAT_EQ(identity.m_02, 0);
	EXPECT_FLOAT_EQ(identity.m_10, 0);
	EXPECT_FLOAT_EQ(identity.m_11, 1);
	EXPECT_FLOAT_EQ(identity.m_12, 0);
	EXPECT_FLOAT_EQ(identity.m_20, 0);
	EXPECT_FLOAT_EQ(identity.m_21, 0);
	EXPECT_FLOAT_EQ(identity.m_22, 1);

	Matrix3D victim(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	EXPECT_FLOAT_EQ(victim.m_00, 1);
	EXPECT_FLOAT_EQ(victim.m_01, 2);
	EXPECT_FLOAT_EQ(victim.m_02, 3);
	EXPECT_FLOAT_EQ(victim.m_10, 4);
	EXPECT_FLOAT_EQ(victim.m_11, 5);
	EXPECT_FLOAT_EQ(victim.m_12, 6);
	EXPECT_FLOAT_EQ(victim.m_20, 7);
	EXPECT_FLOAT_EQ(victim.m_21, 8);
	EXPECT_FLOAT_EQ(victim.m_22, 9);
}

TEST(Matrix3D, Rotation)
{
	Matrix3D op;
	op = Matrix3D::rotateZ(0);
	EXPECT_FLOAT_EQ(op.m_00, 1);
	EXPECT_FLOAT_EQ(op.m_01, 0);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, 0);
	EXPECT_FLOAT_EQ(op.m_11, 1);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);

	op = Matrix3D::rotateZ(Math::PI);
	EXPECT_FLOAT_EQ(op.m_00, -1);
	EXPECT_TRUE(proximate(op.m_01, 0));
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_TRUE(proximate(op.m_10, 0));
	EXPECT_FLOAT_EQ(op.m_11, -1);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);

	op = Matrix3D::rotateZ(Math::PI / 2);
	EXPECT_TRUE(proximate(op.m_00, 0));
	EXPECT_FLOAT_EQ(op.m_01, -1);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, 1);
	EXPECT_TRUE(proximate(op.m_11, 0));
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);

	op = Matrix3D::rotateZ(Math::PI / 4);
	const float sqrt2over2 = sqrt(2.0f) / 2.0f;
	EXPECT_FLOAT_EQ(op.m_00, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_01, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_11, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);

	op = Matrix3D::rotateZ(-Math::PI / 4);
	EXPECT_FLOAT_EQ(op.m_00, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_01, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_11, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);

	op = Matrix3D::rotateZ(Math::PI / 3);
	const float sqrt3over2 = sqrt(3.0f) / 2.0f;
	EXPECT_FLOAT_EQ(op.m_00, .5);
	EXPECT_FLOAT_EQ(op.m_01, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_11, .5);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);

	op = Matrix3D::rotateZ(-Math::PI / 3);
	EXPECT_FLOAT_EQ(op.m_00, .5);
	EXPECT_FLOAT_EQ(op.m_01, sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_11, .5);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	EXPECT_FLOAT_EQ(op.m_20, 0);
	EXPECT_FLOAT_EQ(op.m_21, 0);
	EXPECT_FLOAT_EQ(op.m_22, 1);
}

TEST(Matrix3D, Translation)
{
	Matrix3D translator = Matrix3D::translate(4, 8);
	Vector3D victim(-3, 8, 1);

	Vector3D victimPrime = translator * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 1);
	EXPECT_FLOAT_EQ(victimPrime.y, 16);
	EXPECT_FLOAT_EQ(victimPrime.z, 1);
}

TEST(Matrix3D, MatrixVectorMultiply)
{
	Matrix3D op(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);

	Vector3D victim(1, 2, 3);

	Vector3D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 14);
	EXPECT_FLOAT_EQ(victimPrime.y, 32);
	EXPECT_FLOAT_EQ(victimPrime.z, 50);
}

TEST(Matrix3D, MatrixMatrixMultiply)
{
	Matrix3D first(
		1, 2, 3,
		4, 5, 6,
		7, 8, 9);
	Matrix3D result = first * first;
	EXPECT_FLOAT_EQ(result.m_00, 30);
	EXPECT_FLOAT_EQ(result.m_01, 36);
	EXPECT_FLOAT_EQ(result.m_02, 42);

	EXPECT_FLOAT_EQ(result.m_10, 66);
	EXPECT_FLOAT_EQ(result.m_11, 81);
	EXPECT_FLOAT_EQ(result.m_12, 96);

	EXPECT_FLOAT_EQ(result.m_20, 102);
	EXPECT_FLOAT_EQ(result.m_21, 126);
	EXPECT_FLOAT_EQ(result.m_22, 150);
}