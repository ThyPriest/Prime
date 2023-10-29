
#include "pch.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Prime
{
	void OpenGLRendererAPI::Initialize()
	{

	}

	void OpenGLRendererAPI::SetViewPort(int x, int y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear(bool clearDepthBuffer)
	{
		if (clearDepthBuffer) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
		else { glClear(GL_COLOR_BUFFER_BIT); }
	}

	void OpenGLRendererAPI::DrawIndexed(Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount == 0 ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
