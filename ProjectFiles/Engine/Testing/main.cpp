//============================================================================
// # VOYAGER ENGINE #
// Name: main.cpp
// Module: Testing
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Testing module entry point
//============================================================================

#include <gtest\gtest.h>

void main(int argc, char* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
}