
#include "pch.h"
#include "AssetManager.h"
#include "Prime/Renderer/Renderer.h"
#include "Prime/Platform/OpenGL/OpenGLShader.h"
#include "Prime/Platform/OpenGL/OpenGLTexture.h"

namespace Prime
{
	AssetManager::Data* AssetManager::s_Data = new AssetManager::Data();;

	void AssetManager::Shutdown()
	{
		s_Data->Shaders.clear();
		delete s_Data;
		s_Data = nullptr;
	}

	// Shader
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


	// Texture
	void AssetManager::LoadTexture2D(const std::string& path, const std::string& name, Texture2D::Filter filter)
	{
		Ref<Texture2D> texture;

		switch (Renderer::GetAPI())
		{
		case Prime::API::OpenGL:
			texture = CreateRef<OpenGLTexture2D>(path, filter);
			break;

		case Prime::API::DirectX:
			PRIME_ERROR("DirectX Currently not supported");
			break;

		default:
			PRIME_ERROR("Unknown texture2D");
			break;
		}
		AddTexture2D(name, texture);
	}

	void AssetManager::AddTexture2D(const std::string& name, Ref<Texture2D>& texture)
	{
		PRIME_ASSERT(Texture2DExists(name), "Texture already exist!");
		s_Data->Textures2D[name] = texture;
	}

	Ref<Texture2D>& AssetManager::GetTexture2D(const std::string& name)
	{
		PRIME_ASSERT(!Texture2DExists(name), "Texture not found!");
		return s_Data->Textures2D[name];
	}

	bool AssetManager::Texture2DExists(const std::string& name)
	{
		return s_Data->Textures2D.find(name) != s_Data->Textures2D.end();
	}
}