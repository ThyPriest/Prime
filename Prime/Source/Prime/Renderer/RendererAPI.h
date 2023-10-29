#pragma once

#include "Prime/Core/Core.h"
#include "VertexArray.h"
#include "glm/glm.hpp"

namespace Prime
{
	class PRIME_API RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Initialize() = 0;
		virtual void SetViewPort(int x, int y, uint32_t width, uint32_t height) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear(bool clearDepthBuffer) = 0;

		virtual void DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount) = 0;
		static const API GetAPI() { return s_API; }

		static Scope<RendererAPI> Create();

	private:
		static void SetAPI(API api) { s_API = api; }

	private:
		static API s_API;
		friend class Renderer;
	};
}