
#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLShader.h"

namespace Prime
{
	Ref<Shader> Shader::Create(const std::string& vertSource, const std::string& fragSource)
	{
		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			return CreateRef<OpenGLShader>(vertSource, fragSource, false);
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown shader");
			return nullptr;
			break;
		}
	}
}