/*
* Profiler.h
* Default profiler
*
*  Created on: Aug 14, 2018
*      Author: Fredrik Linde
*/

#ifndef VE_CORE_DEBUG_PROFILER_H
#define VE_CORE_DEBUG_PROFILER_H

#include <Core\Misc\TypeDefs.h>

namespace Profiling
{

	class __declspec(dllexport) Profiler
	{
	public:
		static const VE::uint MAX_FRAME_SAMPLES = 1000;
		static Profiler& getInstance();
	private:
		Profiler() {}
		Profiler(const Profiler&);
		Profiler& operator=(const Profiler&);
		static Profiler instance;
#if PROFILING_ON
		const char* _filename;
		bool _status;
		static const VE::uint MAX_PROFILE_CATEGORIES = 20;
		VE::uint _frame_index;
		VE::uint _categoryIndex;
		VE::uint _used_categories;
		struct ProfileCategory
		{
			const char* name;
			float samples[MAX_FRAME_SAMPLES];
		} categories[MAX_PROFILE_CATEGORIES];
		void writeData() const;
		void writeFrame(VE::uint frame) const;
		char getDelimiter(VE::uint index) const;
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
