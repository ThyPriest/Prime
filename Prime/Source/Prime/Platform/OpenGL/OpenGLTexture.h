#pragma once

#include "Prime/Core/Core.h"
#include "Prime/Renderer/Texture.h"

namespace Prime
{
	class PRIME_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, Filter filter);
		OpenGLTexture2D(std::string path, Filter filter);
		~OpenGLTexture2D();

		uint32_t GetWdth() const override { return m_Width; }
		uint32_t GetHeight() const override { return m_Height; }

		const std::string& GetPath() const override { return m_Path; }
		void SetData(void* data, uint32_t size) override;

		void Bind(uint32_t slot = 0) const override;
		void UnBind() const override;

	private:
		void Load();

	private:
		RendererID m_RendererID = 0;
		uint32_t m_Width = 0, m_Height = 0;
		uint32_t m_DataFormat = 0, m_InternalFormat = 0, m_Channels = 0;
		std::string m_Path = "";
		Filter m_Filter;
		unsigned char* m_Data = nullptr;
	};
}