
#include "pch.h"
#include "Renderer.h"
#include "Prime/Core/AssetManager.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Prime
{
	Renderer::Data* Renderer::s_Data = new Renderer::Data();

	void Renderer::Initialize()
	{
		PRIME_PROFILE_FUNCTION();

		RenderCommand::Initialize();
		InitializeQuadRendering();
	}

	void Renderer::Shutdown()
	{
		PRIME_PROFILE_FUNCTION();

		delete s_Data;
		s_Data = nullptr;
	}

	void Renderer::BeginScene2D(Camera2D& camera2D)
	{
		PRIME_PROFILE_FUNCTION();

		auto shader = AssetManager::GetShader("Quad2D");
		shader->Bind();
		shader->SetMat4("u_ViewProjectionMatrix", camera2D.GetViewProjectionMatrix());

		s_Data->ViewProjection = camera2D.GetViewProjectionMatrix();

		s_Data->QuadIndexCount = 0;
		s_Data->QuadVertexBufferPtr = s_Data->QuadVertexBufferBase;
		s_Data->TextureSlotIndex = 1;
	}

	void Renderer::EndScene2D()
	{
		PRIME_PROFILE_FUNCTION();

		uint32_t dataSize = (uint8_t*)s_Data->QuadVertexBufferPtr - (uint8_t*)s_Data->QuadVertexBufferBase;
		s_Data->QuadVertexBuffer->SetData(s_Data->QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer::DrawQuad2D(Quad2D& quad)
	{
		DrawQuad2D(quad.Posiition, quad.Size, quad.Color);
	}

	void Renderer::DrawQuad2D(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		PRIME_PROFILE_FUNCTION();

		const float texIndex = .0f; // white texture

		s_Data->QuadVertexBufferPtr->Position = pos;
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { .0f, .0f };
		s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y, pos.z };
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, .0f };
		s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = { pos.x, pos.y + size.y, pos.z };
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { .0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = texIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadIndexCount += 6;
	}

	void Renderer::DrawTexture2D(Ref<Texture2D>& texture, Quad2D& quad)
	{
		DrawTexture2D(texture, quad.Posiition, quad.Size, quad.Color);
	}

	void Renderer::DrawTexture2D(Ref<Texture2D>& texture, const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		PRIME_PROFILE_FUNCTION();

		float textureIndex = .0f;
		for (uint32_t x = 1; x < s_Data->TextureSlotIndex; x++)
		{
			if (*s_Data->TextureSlots[x].get() == *texture.get())
			{
				textureIndex = (float)x;
				break;
			}
		}

		if (textureIndex == .0f)
		{
			textureIndex = (float)s_Data->TextureSlotIndex;
			s_Data->TextureSlots[s_Data->TextureSlotIndex] = texture;
		}

		s_Data->QuadVertexBufferPtr->Position = pos;
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { .0f, .0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y, pos.z };
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, .0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadVertexBufferPtr->Position = { pos.x, pos.y + size.y, pos.z };
		s_Data->QuadVertexBufferPtr->Color = color;
		s_Data->QuadVertexBufferPtr->TexCoord = { .0f, 1.0f };
		s_Data->QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data->QuadVertexBufferPtr++;

		s_Data->QuadIndexCount += 6;
	}

	void Renderer::InitializeQuadRendering()
	{
		PRIME_PROFILE_FUNCTION();

		BufferLayout quadLayout = {
			{ ShaderDataType::Float3, "a_Position", false },
			{ ShaderDataType::Float4, "a_Color",    false },
			{ ShaderDataType::Float2, "a_TexCoord", false },
			{ ShaderDataType::Float,  "a_TexIndex", false },
		};

		s_Data->QuadVertexArray = VertexArray::Create();

		s_Data->QuadVertexBuffer = VertexBuffer::Create(s_Data->MaxVertices * sizeof(QuadVertex));
		s_Data->QuadVertexBuffer->SetLayout(quadLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(s_Data->QuadVertexBuffer);

		s_Data->QuadVertexBufferBase = new QuadVertex[s_Data->MaxVertices];
		uint32_t* quadIndices = new uint32_t[s_Data->MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data->MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> QuadIB = IndexBuffer::Create(quadIndices, s_Data->MaxIndices);
		s_Data->QuadVertexArray->SetIndexBuffer(QuadIB);
		delete[] quadIndices;

		int samplers[s_Data->MaxTextureSlots];
		for (uint32_t x = 0; x < s_Data->MaxTextureSlots; x++)
		{
			samplers[x] = x;
		}

		AssetManager::LoadShader("Quad2D", "assets/Shaders/Quad2D.vert", "assets/Shaders/Quad2D.frag");
		s_Data->TextureSlots[0] = Texture2D::Create(1, 1, Texture2D::Filter::Linear);

		auto shader = AssetManager::GetShader("Quad2D");
		shader->Bind();
		shader->SetIntArray("u_Textures", samplers, s_Data->MaxTextureSlots);
	}

	void Renderer::Flush()
	{
		PRIME_PROFILE_FUNCTION();

		for (uint32_t x = 0; x <= s_Data->TextureSlotIndex; x++)
		{
			s_Data->TextureSlots[x]->Bind(x);
		}
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray, s_Data->QuadIndexCount);
	}
}