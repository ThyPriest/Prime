
#include "pch.h"
#include "Renderer.h"
#include "Prime/Core/AssetManager.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Prime
{
	Renderer::Data* Renderer::s_Data = new Renderer::Data();

	void Renderer::Initialize()
	{
		RenderCommand::Initialize();
		InitializeQuadRendering();
	}

	void Renderer::Shutdown()
	{
		delete s_Data;
		s_Data = nullptr;
	}

	void Renderer::BeginScene2D(Camera2D& camera2D)
	{
		auto shader = AssetManager::GetShader("Quad2D");
		shader->Bind();
		shader->SetMat4("u_ViewProjectionMatrix", camera2D.GetViewProjectionMatrix());

		s_Data->WhiteTexture->Bind();
	}

	void Renderer::EndScene2D()
	{
		Flush();
	}

	void Renderer::DrawQuad2D(Quad2D& quad)
	{
		DrawQuad2D(quad.Posiition, quad.Size, quad.Color);
	}

	void Renderer::DrawQuad2D(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		auto shader = AssetManager::GetShader("Quad2D");
		shader->SetFloat4("u_Color", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		shader->SetMat4("u_Transform", transform);
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer::DrawTexture2D(Ref<Texture2D>& texture, Quad2D& quad)
	{
		DrawTexture2D(texture, quad.Posiition, quad.Size, quad.Color);
	}

	void Renderer::DrawTexture2D(Ref<Texture2D>& texture, const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
	{
		auto shader = AssetManager::GetShader("Quad2D");
		shader->SetFloat4("u_Color", color);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		shader->SetMat4("u_Transform", transform);

		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer::InitializeQuadRendering()
	{
		float vertices[5 * 4] = {
			-.5f, -.5f, .0f,  .0f,  .0f, 
			 .5f, -.5f, .0f,  1.0f, .0f,
			 .5f,  .5f, .0f,  1.0f, 1.0f,
			-.5f,  .5f, .0f,  .0f,  1.0f
		};

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		BufferLayout quadLayout = {
			{ ShaderDataType::Float3, "a_Position", false },
			{ ShaderDataType::Float2, "a_TextCoord", false }
		};

		s_Data->QuadVertexArray = VertexArray::Create();

		Ref<VertexBuffer> QuadVB = VertexBuffer::Create(vertices, sizeof(vertices));
		QuadVB->SetLayout(quadLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(QuadVB);

		Ref<IndexBuffer> QuadIB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(QuadIB);

		AssetManager::LoadShader("Quad2D", "assets/Shaders/Quad2D.vert", "assets/Shaders/Quad2D.frag");

		s_Data->WhiteTexture = Texture2D::Create(1, 1, Texture2D::Filter::Linear);
	}

	void Renderer::Flush()
	{

	}
}