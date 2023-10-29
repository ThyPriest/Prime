
#include "pch.h"
#include "OpenGLTexture.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"

namespace Prime
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, Filter filter)
	{
		m_Width = width;
		m_Height = height;
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
		m_Channels = 4;
		m_Filter = filter;
		uint32_t whiteTextureData = 0xffffffff;
		SetData(&whiteTextureData, sizeof(uint32_t));

		switch (filter)
		{
		case Filter::Linear:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;

		case Filter::Nearest:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;

		default:
			PRIME_ASSERT(false, "unknown filter");
			break;
		}
	}

	OpenGLTexture2D::OpenGLTexture2D(std::string path, Filter filter)
	{
		m_Path = path;
		int width = 0, height = 0, channels = 0;
		stbi_set_flip_vertically_on_load(1);

		m_Data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (m_Data)
		{
			m_Width = width;
			m_Height = height;
			m_Channels = channels;
		}

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		if (m_Channels == 4)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
		}

		else if (m_Channels == 3)
		{
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGB;
		}

		m_Filter = filter;

		Load();
		stbi_image_free(m_Data);
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
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void OpenGLTexture2D::Load()
	{
		if (m_Data != nullptr && m_DataFormat != 0)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0,
				m_DataFormat, GL_UNSIGNED_BYTE, m_Data);

			switch (m_Filter)
			{
			case Filter::Linear:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;

			case Filter::Nearest:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;

			default:
				PRIME_ASSERT(false, "unknown filter");
				break;
			}
		}

		else
		{
			m_Width = 1;
			m_Height = 1;
			m_InternalFormat = GL_RGBA8;
			m_DataFormat = GL_RGBA;
			m_Channels = 4;
			uint32_t whiteTextureData = 0xffffffff;
			SetData(&whiteTextureData, sizeof(uint32_t));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			PRIME_WARN("Unable to load texture : {} - defaulting to white texture", m_Path.c_str());
		}

	}
}