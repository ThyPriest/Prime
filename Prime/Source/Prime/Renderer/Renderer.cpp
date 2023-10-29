
#include "pch.h"
#include "Renderer.h"

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

	/*void Renderer::BeginScene2D(Camera2D& camera2D)
	{

	}*/

	void Renderer::EndScene2D()
	{
		Flush();
	}

	void Renderer::DrawQuad2D()
	{
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
	}

	void Renderer::InitializeQuadRendering()
	{
		float vertices[4 * 3] = {
			-.5f, -.5f, .0f,
			 .5f, -.5f, .0f,
			 .5f,  .5f, .0f,
			-.5f,  .5f, .0f,
		};

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

		BufferLayout quadLayout = {
			{ShaderDataType::Float3, "a_Position", false},
		};

		s_Data->QuadVertexArray = VertexArray::Create();

		Ref<VertexBuffer> QuadVB = VertexBuffer::Create(vertices, sizeof(vertices));
		QuadVB->SetLayout(quadLayout);
		s_Data->QuadVertexArray->AddVertexBuffer(QuadVB);

		Ref<IndexBuffer> QuadIB = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		s_Data->QuadVertexArray->SetIndexBuffer(QuadIB);
	}

	void Renderer::Flush()
	{

	}
}