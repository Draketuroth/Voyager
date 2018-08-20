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

TEST(Vector3D, VectorSubtraction)
{
	Vector3D first(8, 3, 9);
	Vector3D second(7, 1, 5);
	Vector3D result = first - second;
	EXPECT_FLOAT_EQ(result.x, 1);
	EXPECT_FLOAT_EQ(result.y, 2);
	EXPECT_FLOAT_EQ(result.z, 4);
	result = second - first;
	EXPECT_FLOAT_EQ(result.x, -1);
	EXPECT_FLOAT_EQ(result.y, -2);
	EXPECT_FLOAT_EQ(result.z, -4);
}

TEST(Vector3D, Perpendicularity)
{
	Vector3D meVector(4, 2);
	Vector3D perp_cw = meVector.perpCwXy();
	Vector3D perp_ccw = meVector.perpCCwXy();
	EXPECT_FLOAT_EQ(perp_cw.x, 2);
	EXPECT_FLOAT_EQ(perp_cw.y, -4);
	EXPECT_FLOAT_EQ(perp_ccw.x, -2);
	EXPECT_FLOAT_EQ(perp_ccw.y, 4);
}

TEST(Vector3D, DotProduct)
{
	Vector3D first(1, 2, 3);
	Vector3D second(4, 5, 6);
	float result = first.dot(second);
	EXPECT_FLOAT_EQ(result, 32);
}

TEST(Vector3D, Magnitude)
{
	Vector3D vec(3, 4, 5);
	float magnitude = vec.magnitude();
	EXPECT_FLOAT_EQ(magnitude, sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

TEST(Vector3D, MagnitudeSquared)
{
	Vector3D vec(3, 4, 5);
	EXPECT_FLOAT_EQ(vec.magnitudeSquared(), 50.0f);

	Vector3D vec2(0, 6, 0);
	EXPECT_FLOAT_EQ(vec2.magnitudeSquared(), 36.0f);
}

TEST(Vector3D, Normalization)
{
	Vector3D vec(1.0f, 2.0f, 3.0f);
	float mag = vec.magnitude();
	Vector3D normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, vec.x / mag);
	EXPECT_FLOAT_EQ(normalized.y, vec.y / mag);
	EXPECT_FLOAT_EQ(normalized.z, vec.z / mag);

	vec = Vector3D(-2.8f, 8.4f, -3.14f);
	mag = vec.magnitude();
	normalized = vec.normalized();
	EXPECT_FLOAT_EQ(normalized.magnitude(), 1.0f);
	EXPECT_FLOAT_EQ(normalized.x, vec.x / mag);
	EXPECT_FLOAT_EQ(normalized.y, vec.y / mag);
	EXPECT_FLOAT_EQ(normalized.z, vec.z / mag);
}