//============================================================================
// # VOYAGER ENGINE #
// Name: Matrix3DTests.cpp
// Module: Testing
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: 3D matrix testing
//============================================================================

#include <gtest\gtest.h>
#include <Math\Matrix\Matrix3D.h>
#include <Math/Matrix/Matrix2DH.h>
#include <Math\Vector\Vector3D.h>
#include <Math\Constants.h>
#include <Core/Misc/TypeDefs.h>
#include "Testing\TestingHelper.h"

using Math::Matrix3D;
using Math::Matrix2DH;
using Math::Vector3D;

// TODO: Temporary solution, find better approach if possible.
template<class T>
void evaluateLastRow(const T& op)
{
	// Check type id
	if (typeid(T) == typeid(Matrix3D))
	{
		// Pointer P should point to final row
		// |  |  |  |  |  |  | 0 | 0 | 1 |
		//					 ^

		// The number of elements in the first two rows
		const Vuint PREVIOUS_ELEMENTS = 6;

		// Reinterpet Matrix member variables as a float array (which it is anyway in memory)
		const float* p = reinterpret_cast<const float*>(&op);
		p += PREVIOUS_ELEMENTS;

		EXPECT_FLOAT_EQ(*p++, 0);
		EXPECT_FLOAT_EQ(*p++, 0);
		EXPECT_FLOAT_EQ(*p, 1);
	}
}

template<class T>
void testScale()
{
	Vector3D victim(6.0f, 5.0f);
	T op = T::scale(0.5f, 2.0f);
	Vector3D victimPrime = op * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 3.0f);
	EXPECT_FLOAT_EQ(victimPrime.y, 10.0f);
}

template<class T>
void testRotation()
{
	T op;
	op = T::rotateZ(0);
	EXPECT_FLOAT_EQ(op.m_00, 1);
	EXPECT_FLOAT_EQ(op.m_01, 0);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, 0);
	EXPECT_FLOAT_EQ(op.m_11, 1);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);

	op = T::rotateZ(Math::PI);
	EXPECT_FLOAT_EQ(op.m_00, -1);
	EXPECT_TRUE(proximate(op.m_01, 0));
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_TRUE(proximate(op.m_10, 0));
	EXPECT_FLOAT_EQ(op.m_11, -1);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);

	op = T::rotateZ(Math::PI / 2);
	EXPECT_TRUE(proximate(op.m_00, 0));
	EXPECT_FLOAT_EQ(op.m_01, -1);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, 1);
	EXPECT_TRUE(proximate(op.m_11, 0));
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);

	op = T::rotateZ(Math::PI / 4);
	const float sqrt2over2 = sqrt(2.0f) / 2.0f;
	EXPECT_FLOAT_EQ(op.m_00, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_01, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_11, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);

	op = T::rotateZ(-Math::PI / 4);
	EXPECT_FLOAT_EQ(op.m_00, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_01, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, -sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_11, sqrt2over2);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);

	op = T::rotateZ(Math::PI / 3);
	const float sqrt3over2 = sqrt(3.0f) / 2.0f;
	EXPECT_FLOAT_EQ(op.m_00, .5);
	EXPECT_FLOAT_EQ(op.m_01, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_11, .5);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);

	op = T::rotateZ(-Math::PI / 3);
	EXPECT_FLOAT_EQ(op.m_00, .5);
	EXPECT_FLOAT_EQ(op.m_01, sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_02, 0);
	EXPECT_FLOAT_EQ(op.m_10, -sqrt3over2);
	EXPECT_FLOAT_EQ(op.m_11, .5);
	EXPECT_FLOAT_EQ(op.m_12, 0);
	evaluateLastRow(op);
}

template<class T>
void testTranslation()
{
	T translator = T::translate(4, 8);
	Vector3D victim(-3, 8, 1);

	Vector3D victimPrime = translator * victim;
	EXPECT_FLOAT_EQ(victimPrime.x, 1);
	EXPECT_FLOAT_EQ(victimPrime.y, 16);
	EXPECT_FLOAT_EQ(victimPrime.z, 1);
}

TEST(Matrix3D, Construction)
{
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

	{
		Matrix2DH identity;
		EXPECT_FLOAT_EQ(identity.m_00, 1);
		EXPECT_FLOAT_EQ(identity.m_01, 0);
		EXPECT_FLOAT_EQ(identity.m_02, 0);
		EXPECT_FLOAT_EQ(identity.m_10, 0);
		EXPECT_FLOAT_EQ(identity.m_11, 1);
		EXPECT_FLOAT_EQ(identity.m_12, 0);

		Matrix2DH victim(
			1, 2, 3,
			4, 5, 6);

		EXPECT_FLOAT_EQ(victim.m_00, 1);
		EXPECT_FLOAT_EQ(victim.m_01, 2);
		EXPECT_FLOAT_EQ(victim.m_02, 3);
		EXPECT_FLOAT_EQ(victim.m_10, 4);
		EXPECT_FLOAT_EQ(victim.m_11, 5);
		EXPECT_FLOAT_EQ(victim.m_12, 6);
	}
}

TEST(Matrix3D, Rotation)
{
	testRotation<Matrix3D>();
	testRotation<Matrix2DH>();
}

TEST(Matrix3D, Translation)
{
	testTranslation<Matrix3D>();
	testTranslation<Matrix2DH>();
}

TEST(Matrix3D, Scaling)
{
	testScale<Matrix3D>();
	testScale<Matrix2DH>();
}

TEST(Matrix3D, MatrixVectorMultiply)
{
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

	{
		Matrix2DH op2(
			1, 2, 3,
			4, 5, 6);

		Vector3D victim(1, 2, 3);

		Vector3D victimPrime = op2 * victim;
		EXPECT_FLOAT_EQ(victimPrime.x, 14);
		EXPECT_FLOAT_EQ(victimPrime.y, 32);
		EXPECT_FLOAT_EQ(victimPrime.z, victim.z);

	}
}

TEST(Matrix3D, MatrixMatrixMultiply)
{
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

	{
		Matrix2DH first(
			1, 2, 3,
			4, 5, 6);
		Matrix2DH result = first * first;
		EXPECT_FLOAT_EQ(result.m_00, 9);
		EXPECT_FLOAT_EQ(result.m_01, 12);
		EXPECT_FLOAT_EQ(result.m_02, 18);

		EXPECT_FLOAT_EQ(result.m_10, 24);
		EXPECT_FLOAT_EQ(result.m_11, 33);
		EXPECT_FLOAT_EQ(result.m_12, 48);
	}
}