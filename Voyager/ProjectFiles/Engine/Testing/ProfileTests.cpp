/*
* ProfileTests.cpp
* Default profiler testing
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#include <gtest\gtest.h>
#include <Core\DebugTools\Profiling\Profiler.h>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;

using Profiling::Profiler;

namespace
{
	char* categories[]{

		"Category1",
		"Category2",
		"Category3"
	};

	const char* const PROFILER_OUTPUT = "profiles.csv";
	const unsigned int NUM_CATEGORIES = sizeof(categories) / sizeof(*categories);
}

string getNextToken(ifstream& file)
{
	char c;
	string ret;

	while (file.good())
	{
		file >> std::noskipws;
		file >> c;
		if (c == ',' || c == '\n')
		{
			break;
		}
		ret += c;
	}
	return ret;
}

bool isAtEndOfFile(ifstream& input)
{
	if (!input.good())
	{
		return false;
	}
	char bit_bucket;
	input >> bit_bucket;
	return !input.good();
}

void writeFrames(unsigned int numFrames)
{
	float sample_number = 0;
	for (float frame = 0; frame < numFrames; frame++)
	{
		profiler.newFrame();

		for (unsigned int cat = 0; cat < NUM_CATEGORIES; cat++)
		{
			profiler.addEntry(categories[cat], sample_number++);

		}
	}
}

void checkFrames(unsigned int numFrames, bool excludeLastFrame = false)
{
	ifstream input(PROFILER_OUTPUT);

	for (unsigned int i = 0; i < NUM_CATEGORIES; i++)
	{
		EXPECT_EQ(getNextToken(input), categories[i]);
	}

	unsigned int profiler_number = 0;
	if (numFrames >= Profiler::MAX_FRAME_SAMPLES)
	{
		profiler_number = (numFrames - Profiler::MAX_FRAME_SAMPLES) * NUM_CATEGORIES;
		numFrames = Profiler::MAX_FRAME_SAMPLES;
	}
	if (excludeLastFrame)
	{
		profiler_number += NUM_CATEGORIES;
		numFrames--;
	}

	for (unsigned int i = 0; i < (numFrames * NUM_CATEGORIES); i++)
	{
		string buf = getNextToken(input);
		EXPECT_EQ(atoi(buf.c_str()), profiler_number++);
	}
	EXPECT_TRUE(isAtEndOfFile(input));
	input.close();
}

void runTestsOnFrames(unsigned int numFrames)
{
	profiler.initialize(PROFILER_OUTPUT);
	writeFrames(numFrames);

	profiler.shutdown();
	checkFrames(numFrames);
}

void writeIncompleteFrames(unsigned int numFrames)
{
	bool wrapped = numFrames >= Profiler::MAX_FRAME_SAMPLES;
	profiler.initialize(PROFILER_OUTPUT);
	writeFrames(numFrames);
	profiler.newFrame();
	profiler.addEntry(categories[0], 99);
	profiler.shutdown();
	checkFrames(numFrames, wrapped);

	profiler.initialize(PROFILER_OUTPUT);
	writeFrames(numFrames);
	profiler.newFrame();
	profiler.addEntry(categories[0], 99);
	profiler.addEntry(categories[1], 100);
	profiler.shutdown();
	checkFrames(numFrames, wrapped);
}

TEST(Profiler, SmallAmountOfFrames)
{
	runTestsOnFrames(5);
}

TEST(Profiler, LargeAmountOfFramesNonCircular)
{
	const unsigned int NUM_FRAMES_THIS_TEST = static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * .8);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profiler, ArrayBoundaries)
{
	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES);
	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES + 1);
	runTestsOnFrames(Profiler::MAX_FRAME_SAMPLES + 2);
}

TEST(Profiler, CirculatingOnePlusSome)
{
	const unsigned int NUM_FRAMES_THIS_TEST =
		static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES + 3);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profiler, GoAroundSeveralTimes)
{
	const unsigned int NUM_FRAMES_THIS_TEST = static_cast<unsigned int>(Profiler::MAX_FRAME_SAMPLES * 3.14);
	runTestsOnFrames(NUM_FRAMES_THIS_TEST);
}

TEST(Profiler, ExcludeIncompleteFrames)
{
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES - 2); // No wrap
	writeIncompleteFrames(Profiler::MAX_FRAME_SAMPLES + 2); // Wrap
}

TEST(Profiler, AddingDuplicateCategoriesInOneFrame)
{
	profiler.initialize(PROFILER_OUTPUT);
	profiler.newFrame();
	profiler.addEntry("My First Category", 1);
	profiler.addEntry("My Second Category", 2);
	bool status;
#if PROFILING_ON
	profiler.checkStatus(&status);
#else
	status = true;
#endif
	EXPECT_TRUE(status);
	profiler.addEntry("My Second Category", 2);
#if PROFILING_ON
	profiler.checkStatus(&status);
#else
		status = false;
#endif
	EXPECT_TRUE(!status);
	profiler.shutdown();
}