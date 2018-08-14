/*
* Vector3DTests.cpp
* 3D matrix testing
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <gtest\gtest.h>
#include <Math\Vector\Vector3D.h>
using Math::Vector3D;

TEST(Vector3D, Constructor)
{
	Vector3D instance(-4.3f, 9.1f, 5.0f);
	EXPECT_FLOAT_EQ(instance.x, -4.3f);
	EXPECT_FLOAT_EQ(instance.y, 9.1f);
	EXPECT_FLOAT_EQ(instance.z, 5.0f);

	Vector3D defaultConstructor;
	EXPECT_FLOAT_EQ(defaultConstructor.x, 0.0f);
	EXPECT_FLOAT_EQ(defaultConstructor.y, 0.0f);
	EXPECT_FLOAT_EQ(defaultConstructor.z, 0.0f);
}

TEST(Vector3D, VectorAddition)
{
	Vector3D first(9, -2, 5);
	Vector3D second(-4, 5.4f, 7);
	Vector3D result = first + second;
	EXPECT_FLOAT_EQ(result.x, 5);
	EXPECT_FLOAT_EQ(result.y, 3.4f);
	EXPECT_FLOAT_EQ(result.z, 12);

}

TEST(Vector3D, ScalarMUltiplication)
{
	Vector3D instance(1, 2, 3);
	Vector3D mutiplied1 = 5 * instance;
	Vector3D mutiplied2 = instance * 5;

	EXPECT_FLOAT_EQ(mutiplied1.x, 5);
	EXPECT_FLOAT_EQ(mutiplied1.y, 10);
	EXPECT_FLOAT_EQ(mutiplied1.z, 15);

	EXPECT_FLOAT_EQ(mutiplied2.x, mutiplied1.x);
	EXPECT_FLOAT_EQ(mutiplied2.y, mutiplied1.y);
	EXPECT_FLOAT_EQ(mutiplied2.z, mutiplied1.z);
}

TEST(Vector3D, AssignmentPlusEquals)
{
	Vector3D source(5, -1245.463f, 763.123f);
	Vector3D another(1, 1, 125.543f);
	another += source;
	EXPECT_FLOAT_EQ(another.x, 6);
	EXPECT_FLOAT_EQ(another.y, -1244.463f);
	EXPECT_FLOAT_EQ(another.z, 888.666f);
}