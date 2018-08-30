/*
* Vector3DTests.cpp
* 3D matrix testing
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <gtest\gtest.h>
#include <Math\Vector\Vector3D.h>
#include <Math/Constants.h>
#include <Core/Misc/TypeDefs.h>
using Math::Vector3D;

void testProjectionAlgorithms(const Vector3D& source, const Vector3D& target)
{
	Vector3D target_normalized = target.normalized();
	Vector3D old_result = source.dot(target_normalized) * target_normalized;
	Vector3D new_result = source.projectOnto(target);
	EXPECT_FLOAT_EQ(old_result.x, new_result.x);
	EXPECT_FLOAT_EQ(old_result.y, new_result.y);
	EXPECT_FLOAT_EQ(old_result.z, new_result.z);
}

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

TEST(Vector3D, ProjectOnto)
{
	Vector3D source(2, 4);
	Vector3D target(1, 0);
	Vector3D result = source.projectOnto(target);
	EXPECT_FLOAT_EQ(result.x, 2.0f);
	EXPECT_FLOAT_EQ(result.y, 0.0f);
	EXPECT_FLOAT_EQ(result.z, 0.0f);

	Vector3D vectors[] =
	{
		Vector3D(1.0f, 2.0f, 3.0f),
		Vector3D(4.8f, 9.1f, 5.6f),
		Vector3D(0.0f,5.0f,0.0f),
		Vector3D(-3.2f, -4.9f, 6.7f),
		Vector3D(2.4f,3.1f, -99.6f)
	};
	const Vuint NUM_VECTORS = sizeof(vectors) / sizeof(*vectors);
	for (Vuint i = 0; i < NUM_VECTORS - 1; i++)
	{
		testProjectionAlgorithms(vectors[i], vectors[i + 1]);
		testProjectionAlgorithms(vectors[i + 1], vectors[i]);
	}

	// Unit circle testing
	Vector3D a(0.5f, sqrt(3.0f) / 2);
	Vector3D b(sqrt(3.0f) / 2, 0.5f);
	float dotResult = a.dot(b);
	EXPECT_FLOAT_EQ(dotResult, cos(Math::PI / 6.0f));
}

TEST(Vector3D, Lerp)
{
	Vector3D source(4.7f, 9.2f, 7.1f);
	Vector3D target(4.7f, 9.2f, 7.1f);
	Vector3D difference = target - source;
	float alpha = 0.0f;
	while (alpha <= 1.0f)
	{
		Vector3D lerp_result1 = lerp(alpha, source, target);
		Vector3D lerp_result2 = source + alpha * difference;
		EXPECT_FLOAT_EQ(lerp_result1.x, lerp_result2.x);
		EXPECT_FLOAT_EQ(lerp_result1.y, lerp_result2.y);
		EXPECT_FLOAT_EQ(lerp_result1.z, lerp_result2.z);
		alpha += 0.01f;
	}
}