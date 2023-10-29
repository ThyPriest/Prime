
#include "pch.h"
#include "AssetManager.h"
#include "Prime/Renderer/Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLShader.h"

namespace Prime
{
	AssetManager::Data* AssetManager::s_Data = new AssetManager::Data();;

	void AssetManager::Shutdown()
	{
		s_Data->Shaders.clear();
		delete s_Data;
		s_Data = nullptr;
	}

	void AssetManager::LoadShader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
	{
		Ref<Shader> shader;

		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			shader = CreateRef<OpenGLShader>(vertSrc, fragSrc, true);
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown shader");
			break;
		}

		AddShader(name, shader);
	}

	void AssetManager::AddShader(const std::string& name, Ref<Shader>& shader)
	{
		PRIME_ASSERT(ShaderExists(name), "Shader already exist!");
		s_Data->Shaders[name] = shader;
	}

	Ref<Shader>& AssetManager::GetShader(const std::string& name)
	{
		PRIME_ASSERT(!ShaderExists(name), "Shader not found!");
		return s_Data->Shaders[name];
	}

	bool AssetManager::ShaderExists(const std::string& name)
	{
		return s_Data->Shaders.find(name) != s_Data->Shaders.end();
	}
}