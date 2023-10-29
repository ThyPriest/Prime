#pragma once

#include <memory>

#ifdef PRIME_BUILD_DLL
#define PRIME_API __declspec(dllexport)
#else
#define PRIME_API __declspec(dllimport)
#endif // PRIME_PLATFORM_WINDOWS

namespace Prime
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename TClass, typename ... TArgs>
	constexpr Scope<TClass> CreateScope(TArgs&& ... args)
	{
		return std::make_unique<TClass>(std::forward<TArgs>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename TClass, typename ... TArgs>
	constexpr Ref<TClass> CreateRef(TArgs&& ... args)
	{
		return std::make_shared<TClass>(std::forward<TArgs>(args)...);
	}
}