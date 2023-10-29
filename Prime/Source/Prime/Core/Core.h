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

	enum class API
	{
		OpenGL, DirectX
	};

	using RendererID = uint32_t;

	enum class ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3,
		Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:      return 4;
		case ShaderDataType::Float2:     return 4 * 2;
		case ShaderDataType::Float3:     return 4 * 3;
		case ShaderDataType::Float4:     return 4 * 4;
		case ShaderDataType::Mat3:       return 4 * 3 * 3;
		case ShaderDataType::Mat4:       return 4 * 4 * 4;
		case ShaderDataType::Int:        return 4;
		case ShaderDataType::Int2:       return 4 * 2;
		case ShaderDataType::Int3:       return 4 * 3;
		case ShaderDataType::Int4:       return 4 * 4;
		case ShaderDataType::Bool:       return 1;
		}
		return 0;

	}

	static uint32_t ShaderDataTypeCount(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3; // 3* float3
		case ShaderDataType::Mat4:    return 4; // 4* float4
		case ShaderDataType::Int:     return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}
		return 0;
	}
}