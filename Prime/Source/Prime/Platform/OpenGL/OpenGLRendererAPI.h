#pragma once

#include "Prime/Core/Core.h"
#include "Prime/Renderer/RendererAPI.h"

namespace Prime
{
	class PRIME_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		OpenGLRendererAPI() = default;

		void Initialize() override;
		void SetViewPort(int x, int y, uint32_t width, uint32_t height) override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear(bool clearDepthBuffer) override;

		void DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
	};
}