#pragma once

#include "Core.h"
#include "Prime/Renderer/Shader.h"
#include "Prime/Renderer/Texture.h"

namespace Prime
{
	class PRIME_API AssetManager
	{
	public:
		static void Shutdown();

		static void LoadShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);
		static void AddShader(const std::string& name, Ref<Shader>& shader);
		static Ref<Shader>& GetShader(const std::string& name);
		static bool ShaderExists(const std::string& name);

		static void LoadTexture2D(const std::string& path, const std::string& name, Texture2D::Filter filter);
		static void AddTexture2D(const std::string& name, Ref<Texture2D>& texture);
		static Ref<Texture2D>& GetTexture2D(const std::string& name);
		static bool Texture2DExists(const std::string& name);

	private:
		struct Data
		{
			std::unordered_map<std::string, Ref<Shader>> Shaders;
			std::unordered_map<std::string, Ref<Texture2D>> Textures2D;
		};

		static Data* s_Data;
	};
}