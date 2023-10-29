#pragma once

#include "Prime/Core/Core.h"

namespace Prime
{
	class PRIME_API Timer
	{
	public:
		Timer(const char* name);
		~Timer();

		void Stop();

	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}
