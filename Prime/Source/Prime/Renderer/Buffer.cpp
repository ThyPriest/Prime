
#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLBuffer.h"

namespace Prime
{
	// Vertex Buffer
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown vertex buffer");
			return nullptr;
			break;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown vertex buffer");
			return nullptr;
			break;
		}
	}

	// Index Buffer
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, count);
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown vertex buffer");
			return nullptr;
			break;
		}
	}
}