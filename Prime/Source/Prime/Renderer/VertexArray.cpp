
#include "pch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLVertexArray.h"

namespace Prime
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown vertex array");
			return nullptr;
			break;
		}
	}
}