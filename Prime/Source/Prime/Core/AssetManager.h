#pragma once

#include "Core.h"
#include "Prime/Renderer/Shader.h"

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

	private:
		struct Data
		{
			std::unordered_map<std::string, Ref<Shader>> Shaders;
		};

		static Data* s_Data;
	};
}