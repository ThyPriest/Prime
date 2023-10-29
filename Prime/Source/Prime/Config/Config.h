#pragma once

#include "Prime/Core/Logger.h"
#include "Prime/Profiler/Profiler.h"

//Logger
#ifdef PRIME_DEBUG
#define PRIME_ENABLE_LOG
#define PRIME_ENABLE_ASSERT
#define PRIME_PROFILE
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

// Profiler
// Check for defferent compilers
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
#define PRIME_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define PRIME_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define PRIME_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define PRIME_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define PRIME_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define PRIME_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define PRIME_FUNC_SIG __func__
#else
#define PRIME_FUNC_SIG "PRIME_FUNC_SIG unknown!"
#endif

#ifdef PRIME_PROFILE
#define PRIME_PROFILE_BEGIN(name, filepath)         ::Prime::Profiler::BeginSession(name, filepath)
#define PRIME_PROFILE_END()                         ::Prime::Profiler::EndSession()
#define PRIME_PROFILE_SCOPE(name)                   ::Prime::Timer timer##__LINE__(name); 
#define PRIME_PROFILE_FUNCTION()                    ::Prime::Timer timer##__LINE__(PRIME_FUNC_SIG); 

#else
#define PRIME_PROFILE_BEGIN(name, filepath)      void()0
#define PRIME_PROFILE_END()                      void()0
#define PRIME_PROFILE_FUNCTION(name)             void()0
#define PRIME_PROFILE_SCOPE()                    void()0    

#endif // PRIME_PROFILE
