#pragma once

#include "Prime/Core/Core.h"
#include "RendererAPI.h"

namespace Prime
{
	class PRIME_API RenderCommand
	{
	public:
		inline static void Initialize();
		inline static void SetViewport(int x, int y, uint32_t width, uint32_t height);
		inline static void SetViewport(uint32_t width, uint32_t height);

		inline static void SetClearColor(const glm::vec4& color);
		inline static void Clear(bool clearDepthBuffer = true);

		inline static void DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

	private:
		static Scope<RendererAPI> s_RendererAPI;
	};
}