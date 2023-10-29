
#include "pch.h"
#include "OpenGLTexture2D.h"
#include "glad/glad.h"

namespace Prime
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, TextureFilter filter)
	{
		m_Width = width;
		m_Height = height;
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		m_Channels = 4;
		uint32_t whiteTextureData = 0xffffffff;
		SetData(&whiteTextureData, sizeof(uint32_t));

		switch (filter)
		{
		case TextureFilter::Linear:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;

		case TextureFilter::Nearest:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;

		default:
			PRIME_ASSERT(false, "unknown filter");
			break;
		}
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bytesPerPixel = m_DataFormat == GL_RGBA ? 4 : 3;
		PRIME_ASSERT(!size == m_Width * m_Height * bytesPerPixel, "Data must be entire texture");
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0,
			m_DataFormat, GL_UNSIGNED_BYTE, data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}