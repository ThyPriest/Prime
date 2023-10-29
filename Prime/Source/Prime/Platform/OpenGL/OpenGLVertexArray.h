#pragma once

#include "Prime/Core/Core.h"
#include "Prime/Renderer/VertexArray.h"

namespace Prime
{
	class PRIME_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void UnBind() const override;

		void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }

		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
		Ref<IndexBuffer>& GetIndexBuffer() override { return m_IndexBuffer; };

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_VertexBufferIndex = 0;
		Ref<IndexBuffer> m_IndexBuffer;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
	};
}