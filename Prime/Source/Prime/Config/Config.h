#pragma once

#include "Prime/Core/Logger.h"

//Logger
#ifdef PRIME_DEBUG
#define PRIME_ENABLE_LOG
#define PRIME_ENABLE_ASSERT
#endif // PRIME_DEBUG

#ifdef PRIME_PLATFORM_WINDOWS
#define PRIME_BREAK  __debugbreak();
#endif // PRIME_PLATFORM_WINDOWS

#ifdef PRIME_ENABLE_LOG
#define PRIME_TRACE(...)       ::Prime::Logger::Trace(__VA_ARGS__)
#define PRIME_LOG(...)         ::Prime::Logger::Log(__VA_ARGS__)
#define PRIME_INFO(...)        ::Prime::Logger::Info(__VA_ARGS__)
#define PRIME_WARN(...)        ::Prime::Logger::Warn(__VA_ARGS__)
#define PRIME_ERROR(...)       ::Prime::Logger::Error(__VA_ARGS__)


#else
#define PRIME_TRACE(...)     void()0
#define PRIME_LOG(...)       void()0
#define PRIME_INFO(...)      void()0
#define PRIME_ERROR(...)     void()0
#define PRIME_WARN(...)      void()0


#endif // PRIME_ENABLE_LOG


//ASSERTION
#ifdef PRIME_ENABLE_ASSERT
#define PRIME_ASSERT(x, ...) { if((x)) { PRIME_ERROR("Assertion failed: {0}", __VA_ARGS__); PRIME_BREAK }}
#else
#define PRIME_ASSERT(x, ...)

#endif // PRIME_ENABLE_ASSERT