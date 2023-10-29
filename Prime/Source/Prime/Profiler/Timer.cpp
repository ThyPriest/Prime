
#include "pch.h"
#include "Timer.h"
#include "Profiler.h"

namespace Prime
{
	Timer::Timer(const char* name)
	{
		m_Name = name;
		m_StartTimepoint = std::chrono::steady_clock::now();
		m_Stopped = false;
	}

	Timer::~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Timer::Stop()
	{
		auto endTimepoint = std::chrono::steady_clock::now();
		auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };

		auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() \
			- std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

		Profiler::WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });
		m_Stopped = true;
	}
}