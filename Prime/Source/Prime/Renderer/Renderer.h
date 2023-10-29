#pragma once

#include "Prime/Core/Core.h"
#include "RenderCommand.h"
#include "Camera2D.h"
#include "Texture.h"

namespace Prime
{
	struct Quad2D
	{
		glm::vec3 Posiition = glm::vec3(0.0f);
		glm::vec4 Color = glm::vec4(1.0f);
		glm::vec2 Size = glm::vec2(.2f);
	};

	class PRIME_API Renderer
	{
	public:
		static void Initialize();
		static void Shutdown();

		static const API GetAPI() { return RendererAPI::GetAPI(); }

		static void BeginScene2D(Camera2D& camera2D);
		static void EndScene2D();

		// Primitives
		// Quad2D
		static void DrawQuad2D(Quad2D& quad);
		static void DrawQuad2D(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

		// Textureed Quad2D
		static void DrawTexture2D(Ref<Texture2D>& texture, Quad2D& quad);
		static void DrawTexture2D(Ref<Texture2D>& texture, const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);

	private:
		static void SetAPI(API api) { RendererAPI::SetAPI(api); }

		static void InitializeQuadRendering();
		static void Flush();

	private:
		struct QuadVertex
		{
			glm::vec3 Position = glm::vec3(.0f);
			glm::vec4 Color = glm::vec4(1.0f);
			glm::vec2 TexCoord = glm::vec2(.2f);
		};

		struct Data
		{
			glm::mat4 ViewProjection = glm::mat4(1.0f);

			const uint32_t MaxQuads = 1000;
			const uint32_t MaxVertices = MaxQuads * 4;
			const uint32_t MaxIndices = MaxQuads * 6;
			uint32_t QuadIndexCount = 0;

			Ref<VertexArray> QuadVertexArray;
			Ref<VertexBuffer> QuadVertexBuffer;
			Ref<Texture2D> WhiteTexture;

			QuadVertex* QuadVertexBufferBase = nullptr;
			QuadVertex* QuadVertexBufferPtr = nullptr;
		};

		static Data* s_Data;
		friend class Application;
	};
}