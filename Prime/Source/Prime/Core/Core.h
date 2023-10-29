#pragma once

#ifdef PRIME_BUILD_DLL
#define PRIME_API __declspec(dllexport)
#else
#define PRIME_API __declspec(dllimport)
#endif // PRIME_PLATFORM_WINDOWS