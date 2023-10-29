
#include "pch.h"
#include "GraphicsContext.h"
#include "Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLGraphicsContext.h"

namespace Prime
{
	Scope<GraphicsContext> GraphicsContext::Create(GLFWwindow* window)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			return CreateScope<OpenGLGraphicsContext>(window);
			break;

		case API::DirectX:
			PRIME_ERROR("DirectX currently not supported");
			break;

		default:
			PRIME_ASSERT(true, "Unknown graphics context");
			break;
		}
	}
}