/*
* main.cpp
* Testing initialization
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <gtest\gtest.h>

void main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
}