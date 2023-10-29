
#include "pch.h"
#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Prime
{
	Ref<spdlog::logger> Logger::logger;

	void Logger::Initialize()
	{
		spdlog::set_pattern("%n: [%b-%d-%Y %I:%M %p]: %v %$");
		logger = spdlog::stdout_color_mt("PRIME");
		logger->set_level(spdlog::level::trace);
	}

	void Logger::Shutdown()
	{
		spdlog::shutdown();
	}
}
