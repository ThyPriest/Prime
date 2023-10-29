
#include "pch.h"
#include "RenderCommand.h"

namespace Prime
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

	inline void RenderCommand::Initialize()
	{
		PRIME_PROFILE_FUNCTION();

		s_RendererAPI->Initialize();
	}

	inline void RenderCommand::SetViewport(int x, int y, uint32_t width, uint32_t height)
	{
		PRIME_PROFILE_FUNCTION();

		s_RendererAPI->SetViewport(x, y, width, height);
	}

	inline void RenderCommand::SetViewport(uint32_t width, uint32_t height)
	{
		PRIME_PROFILE_FUNCTION();

		s_RendererAPI->SetViewport(0, 0, width, height);
	}

	inline void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		PRIME_PROFILE_FUNCTION();

		s_RendererAPI->SetClearColor(color);
	}

	inline void RenderCommand::Clear(bool clearDepthBuffer)
	{
		PRIME_PROFILE_FUNCTION();

		s_RendererAPI->Clear(clearDepthBuffer);
	}

	inline void RenderCommand::DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		PRIME_PROFILE_FUNCTION();

		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray, indexCount);
	}
}