//============================================================================
// # VOYAGER ENGINE #
// Name			: ClockTests.cpp
// Module		: Testing
// Author		: Fredrik Linde
// Created on	: Aug 14, 2018
// Description	: Voyager default clock system testing
//============================================================================

#include <gtest\gtest.h>
#include <Core\Timing\Clock.h>
#include <QtTest\qtest.h>
#include <QtCore\qdebug.h>
#include <iostream>
using std::cout;
using Timing::Clock;

TEST(Clock, Initialize)
{
	Clock clock;
	EXPECT_TRUE(clock.initialize());
	EXPECT_TRUE(clock.shutdown());
}

TEST(Clock, FrameTimeMeasuring)
{
	Clock clock;

#ifdef OVERNIGHT_TESTS
	EXPECT_TRUE(clock.initialize());
	QTest::qSleep(1000);
	clock.lap();
	float timed_time = clock.lastLapTime();
	EXPECT_TRUE(0.9f < timed_time);
	EXPECT_TRUE(timed_time < 1.1f);
	clock.lap();
	QTest::qSleep(500);
	clock.lap();
	timed_time = clock.lastLapTime();
	EXPECT_TRUE(0.4f < timed_time);
	EXPECT_TRUE(timed_time < 0.6f);

	const int NUM_TESTS = 10 + rand() % 100;
	const float THRESHOLD = 0.01f;
	for (int i = 0; i < NUM_TESTS; ++i)
	{
		cout << ".";
		int curr_test_millisec = rand() % 10000;
		float curr_test_sec = curr_test_millisec / 1000.0f;
		clock.lap();
		QTest::qSleep(curr_test_millisec);
		clock.lap();
		float elapsed_sec = clock.lastLapTime();
		EXPECT_TRUE((curr_test_sec - THRESHOLD) < elapsed_sec);
		EXPECT_TRUE(elapsed_sec < (curr_test_sec + THRESHOLD));
	}

#endif

	clock.lap();
	EXPECT_TRUE(clock.shutdown());

}