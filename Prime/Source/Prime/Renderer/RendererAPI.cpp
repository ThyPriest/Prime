
#include "pch.h"
#include "RendererAPI.h"
#include "Prime/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Prime
{
	API RendererAPI::s_API;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case Prime::API::OpenGL:
			return CreateScope<OpenGLRendererAPI>();
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX currently not supported");
			break;

		default:
			PRIME_ASSERT(true, "Unknown rendererAPI");
			break;
		}

	}
}