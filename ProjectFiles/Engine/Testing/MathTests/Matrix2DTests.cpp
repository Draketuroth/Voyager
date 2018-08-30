//============================================================================
// # VOYAGER ENGINE #
// Name			: Matrix2DTests.cpp
// Module		: Testing
// Author		: Fredrik Linde
// Created on	: Aug 14, 2018
// Description	: 2D matrix testing
//============================================================================

#include <cmath>
#include <gtest\gtest.h>
#include <Math\Matrix\Matrix2D.h>
#include <Math\Constants.h>

#include "Testing\TestingHelper.h"

using Math::Matrix2D;
using Math::Vector2D;

TEST(Matrix2D, Construction)
{
	Matrix2D identity;
	EXPECT_FLOAT_EQ(identity.m_00, 1.0f);
	EXPECT_FLOAT_EQ(identity.m_01, 0.0f);
	EXPECT_FLOAT_EQ(identity.m_10, 0.0f);
	EXPECT_FLOAT_EQ(identity.m_11, 1.0f);

	Matrix2D victim(
		1, 2,
		3, 4);
	EXPECT_FLOAT_EQ(victim.m_00, 1);
	EXPECT_FLOAT_EQ(victim.m_01, 2);
	EXPECT_FLOAT_EQ(victim.m_10, 3);
	EXPECT_FLOAT_EQ(victim.m_11, 4);
}

TEST(Matrix2D, Rotation) 
{
	Matrix2D op;
	op = Matrix2D::rotate(0);
	EXPECT_FLOAT_EQ(op.m_00, 1);
	EXPECT_FLOAT_EQ(op.m_01, 0);
	EXPECT_FLOAT_EQ(op.m_10, 0);
	EXPECT_FLOAT_EQ(op.m_11, 1);

	op = Matrix2D::rotate(Math::PI);
	EXPECT_FLOAT_EQ(op.m_00, -1);
	EXPECT_TRUE(proximate(op.m_01, 0));
	EXPECT_TRUE(proximate(op.m_10, 0));
	EXPECT_FLOAT_EQ(op.m_11, -1);

	op = Matrix2D::rotate(Math::PI / 2);
	EXPECT_TRUE(proximate(op.m_00, 0));
	EXPECT_FLOAT_EQ(op.m_01, -1);
	EXPECT_FLOAT_EQ(op.m_10, 1);
	EXPECT_TRUE(proximate(op.m_11, 0));

	op = Matrix2D::rotate(Math::PI / 4);
	const float sqrt2over2 = sqrt(2.0f)/2.0f;
	EXPECT_FLOAT_EQ(op.m_00, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_01, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_10, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_11, sqrt2over2);

	op = Matrix2D::rotate(-Math::PI / 4);
	EXPECT_FLOAT_EQ(op.m_00, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_01, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_10, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_11, sqrt2over2);

	op = Matrix2D::rotate(Math::PI / 3);
	const float sqrt3over2 = sqrt(3.0f)/2.0f;
	EXPECT_FLOAT_EQ(op.m_00, .5);
	EXPECT_FLOAT_EQ(op.m_01, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_10, sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_11, .5);

	op = Matrix2D::rotate(-Math::PI / 3);
	EXPECT_FLOAT_EQ(op.m_00, .5);
	EXPECT_FLOAT_EQ(op.m_01, sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_10, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_11, .5);

}

TEST(Matrix2D, MatrixVectorMultiply)
{
	Matrix2D op(2, -3, 
				4, -5);
	Vector2D victim(3, 9);
	Vector2D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x , -21.0f);
	EXPECT_FLOAT_EQ(victimPrime.y , -33.0f);
}