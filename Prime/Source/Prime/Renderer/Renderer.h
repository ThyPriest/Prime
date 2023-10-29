#pragma once

#include "Prime/Core/Core.h"
#include "RenderCommand.h"

namespace Prime
{
	class PRIME_API Renderer
	{
	public:
		static const API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		static void SetAPI(API api) { RendererAPI::SetAPI(api); }

	private:
		friend class Application;
	};
}