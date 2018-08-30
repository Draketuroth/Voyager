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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	getchar();
}