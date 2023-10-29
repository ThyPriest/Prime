#pragma once

#include "Prime/Core/Core.h"
#include <string>

namespace Prime
{
	class Texture
	{
	public:
		enum class Filter
		{
			Nearest,
			Linear
		};

		virtual ~Texture() = default;

		virtual uint32_t GetWdth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual const std::string& GetPath() const = 0;
		virtual void SetData(void* data, uint32_t size) = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;
		virtual void UnBind() const = 0;
	};

	class PRIME_API Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(uint32_t width, uint32_t height, Filter filter);
	};
}