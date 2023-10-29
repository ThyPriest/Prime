#pragma once

#include "Prime/Core/Core.h"
#include "Timer.h"
#include <chrono>
#include <string>
#include <mutex>
#include <sstream>

namespace Prime
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	struct ProfilerResult
	{
		std::string Name;

		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
	};

	struct ProfilerSession
	{
		std::string Name;
	};

	class PRIME_API Profiler
	{
	public:
		static void BeginSession(const std::string& name, const std::string& filepath = "results.json");
		static void EndSession();

		static void Shutdown();
		static void WriteProfile(const ProfilerResult& result);

	private:
		static void WriteHeader();
		static void WriteFooter();
		static void InternalEndSession();

	private:
		struct Data
		{
			std::mutex Mutex;
			ProfilerSession* CurrentSession = nullptr;
			std::ofstream OutputStream;
		};

		static Data* s_Data;
	};
}