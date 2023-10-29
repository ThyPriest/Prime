
#include "pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLTexture2D.h"

namespace Prime
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height, TextureFilter filter)
	{
		switch (Renderer::GetAPI())
		{
		case API::OpenGL:
			return CreateRef<OpenGLTexture2D>(width, height, filter);
			break;

		case API::DirectX:
			PRIME_ERROR("DirectX currently not supported");
			return nullptr;
			break;

		default:
			PRIME_ASSERT(true, "unknow Texture2D");
			return nullptr;
			break;
		}
	}
}
