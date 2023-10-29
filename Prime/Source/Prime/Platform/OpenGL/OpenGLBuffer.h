#pragma once

#include "Prime/Core/Core.h"
#include "Prime/Renderer/Buffer.h"

namespace Prime
{
	class PRIME_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void UnBind() const override;
		void SetData(const void* data, uint32_t size) override;

		const BufferLayout& GetLayout() const override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

	private:
		RendererID m_RendererID = 0;
		BufferLayout m_Layout;
	};

	class PRIME_API OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void UnBind() const override;
		uint32_t GetCount() const override { return m_Count; }

	private:
		RendererID m_RendererID = 0;
		uint32_t m_Count = 0;
	};
}