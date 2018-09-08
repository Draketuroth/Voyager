//============================================================================
// # VOYAGER ENGINE #
// Name: Profiler.h
// Module: Core
// Author: Fredrik Linde
// Created on: Aug 14, 2018
// Description: Voyager custom profiler
//============================================================================

#ifndef VE_CORE_DEBUG_PROFILER_H
#define VE_CORE_DEBUG_PROFILER_H

#include <Core\Misc\TypeDefs.h>

namespace Profiling
{

	class __declspec(dllexport) Profiler
	{
	public:
		static const uint MAX_FRAME_SAMPLES = 1000;
		static Profiler& getInstance();
	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler instance;
#if PROFILING_ON
		const char* _filename;
		bool _status;
		static const uint MAX_PROFILE_CATEGORIES = 20;
		uint _frame_index;
		uint _categoryIndex;
		uint _used_categories;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];
		void writeData() const;
		void writeFrame(uint frame) const;
		char getDelimiter(uint index) const;
		bool currentFrameComplete() const;
		bool wrapped() const;
		void checkForDuplicateCategory(const char* category);
#endif
	public:
#if PROFILING_ON
		void initialize(const char* file);
		void shutdown();
		void newFrame();
		void addEntry(const char* category, float time);
		void checkStatus(bool* status) const;
#else
		void initialize(const char* file) {}
		void shutdown() {}
		void newFrame() {}
		void addEntry(const char* category, float time) {}
		void checkIsGood(bool* status) const {}
#endif
	};

	#define profiler Profiling::Profiler::getInstance()

}

#endif
