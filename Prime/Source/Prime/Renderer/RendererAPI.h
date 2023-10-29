#pragma once

#include "Prime/Core/Core.h"

namespace Prime
{
	class PRIME_API RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		static const API GetAPI() { return s_API; }

		static Scope<RendererAPI> Create();

	private:
		static void SetAPI(API api) { s_API = api; }

	private:
		static API s_API;
		friend class Renderer;
	};
}