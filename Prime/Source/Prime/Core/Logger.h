#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Prime
{
	class PRIME_API Logger
	{
	public:
		static void Initialize();
		static void Shutdown();

		// Trace White
		template<typename... Args>
		static void Trace(fmt::format_string<Args...>fmt, Args &&...args)
		{
			logger->trace(fmt, std::forward<Args>(args)...);
		}

		template<typename T>
		static void Trace(const T& message)
		{
			logger->trace(message);
		}

		// Log Green
		template<typename... Args>
		static void Log(fmt::format_string<Args...>fmt, Args &&...args)
		{
			logger->info(fmt, std::forward<Args>(args)...);
		}

		template<typename T>
		static void Log(const T& message)
		{
			logger->info(message);
		}

		// Info Blue
		template<typename... Args>
		static void Info(fmt::format_string<Args...>fmt, Args &&...args)
		{
			logger->debug(fmt, std::forward<Args>(args)...);
		}

		template<typename T>
		static void Info(const T& message)
		{
			logger->debug(message);
		}

		// Warn Yellow
		template<typename... Args>
		static void Warn(fmt::format_string<Args...>fmt, Args &&...args)
		{
			logger->warn(fmt, std::forward<Args>(args)...);
		}

		template<typename T>
		static void Warn(const T& message)
		{
			logger->warn(message);
		}

		// Error Blue
		template<typename... Args>
		static void Error(fmt::format_string<Args...>fmt, Args &&...args)
		{
			logger->error(fmt, std::forward<Args>(args)...);
		}

		template<typename T>
		static void Error(const T& message)
		{
			logger->error(message);
		}

	private:
		static Ref<spdlog::logger> logger;
	};
}