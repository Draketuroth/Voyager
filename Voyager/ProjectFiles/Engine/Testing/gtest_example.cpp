#include <gtest\gtest.h>

TEST(MyArbitraryCategoryName, MyArbitraryTestName)
{
	int i = 7;
	int j = 10;
	int asdf = i * j;
	EXPECT_EQ(60, asdf);
	EXPECT_TRUE(asdf == 90);
}

TEST(MyArbitraryCategoryName, SomeOtherTestName)
{

}