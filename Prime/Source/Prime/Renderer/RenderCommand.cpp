
#include "pch.h"
#include "RenderCommand.h"

namespace Prime
{
	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

	inline void RenderCommand::Initialize()
	{
		s_RendererAPI->Initialize();
	}

	inline void RenderCommand::SetViewPort(int x, int y, uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewPort(x, y, width, height);
	}

	inline void RenderCommand::SetViewPort(uint32_t width, uint32_t height)
	{
		s_RendererAPI->SetViewPort(0, 0, width, height);
	}

	inline void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	inline void RenderCommand::Clear(bool clearDepthBuffer)
	{
		s_RendererAPI->Clear(clearDepthBuffer);
	}

	inline void RenderCommand::DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		s_RendererAPI->DrawIndexed(vertexArray, indexCount);
	}
}