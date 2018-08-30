//============================================================================
// # VOYAGER ENGINE #
// Name: Profiler.cpp
// Module: Core
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Voyager custom profiler
//============================================================================

#include <Core\DebugTools\Profiling\Profiler.h>

#ifdef PROFILING_ON
#include <cassert>
#include <iostream>
#include <fstream>
#endif // PROFILING_ON

namespace Profiling
{

	Profiler Profiler::instance;

	Profiler& Profiler::getInstance()
	{
		return instance;
	}

#ifdef PROFILING_ON

	using std::ofstream;
	using std::ios;

	static ofstream out_file;

	void Profiler::initialize(const char* file)
	{
		_filename = file;
		_status = true;
		_frame_index = -1;
		_categoryIndex = 0;
		_used_categories = 0;
	}

	void Profiler::shutdown()
	{
		writeData();
	}

	void Profiler::newFrame()
	{
		assert(_status);
		if (_frame_index > 0)
		{
			assert(_categoryIndex == _used_categories);
		}
		_frame_index++;
		_categoryIndex = 0;
	}

	void Profiler::addEntry(const char* category, float time)
	{
		assert(_categoryIndex < MAX_PROFILE_CATEGORIES);
		ProfileCategory& pc = categories[_categoryIndex];

		if (_frame_index == 0)
		{
			pc.name = category;
			_used_categories++;
			checkForDuplicateCategory(category);
		}
		else
		{
			assert(pc.name == category && category != NULL);
			assert(_categoryIndex < _used_categories);
		}
		_categoryIndex++;
		pc.samples[_frame_index % MAX_FRAME_SAMPLES] = time;
	}

	void Profiler::checkStatus(bool* status) const
	{
		*status = _status;
	}

	void Profiler::checkForDuplicateCategory(const char* category)
	{
		for (Vuint i = 0; i < _categoryIndex; i++)
		{
			_status &= (strcmp(categories[i].name, category) != 0);
		}
	}

	void Profiler::writeFrame(Vuint frame) const
	{
		for (Vuint cat = 0; cat < _used_categories; cat++)
		{
			out_file << categories[cat].samples[frame];
			out_file << getDelimiter(cat);
		}
	}

	char Profiler::getDelimiter(Vuint index) const
	{
		return ((index + 1) < _used_categories) ? ',' : '\n';
	}

	bool Profiler::wrapped() const
	{
		return _frame_index >= MAX_FRAME_SAMPLES && _frame_index != -1;
	}

	void Profiler::writeData() const
	{
		out_file.open(_filename, ios::trunc);

		// Write category headers
		for (Vuint i = 0; i < _used_categories; i++)
		{
			out_file << categories[i].name;
			out_file << getDelimiter(i);
		}

		Vuint end_index;
		Vuint start_index;

		if (wrapped())
		{
			Vuint end_index = _frame_index % MAX_FRAME_SAMPLES;
			Vuint start_index = (end_index + 1) % MAX_FRAME_SAMPLES;

			while (start_index != end_index)
			{
				writeFrame(start_index);
				start_index = (start_index + 1) % MAX_FRAME_SAMPLES;
			}
			if (currentFrameComplete())
			{
				writeFrame(start_index);
			}
		}
		else
		{
			Vuint num_actual_frames = _frame_index;
			if (currentFrameComplete())
			{
				num_actual_frames++;
			}
			start_index = 0;
			end_index = num_actual_frames;
			while (start_index < end_index)
			{
				writeFrame(start_index++);
			}
		}
		out_file.close();
	}

	bool Profiler::currentFrameComplete() const
	{

		return _categoryIndex == _used_categories;
	}
#endif
}