#pragma once

#include "Prime/Core/Core.h"
#include "RenderCommand.h"

namespace Prime
{
	class PRIME_API Renderer
	{
	public:
		static void Initialize();
		static void Shutdown();

		static const API GetAPI() { return RendererAPI::GetAPI(); }

		//static void BeginScene2D(Camera2D& camera2D);
		static void EndScene2D();

		// Primitives
		static void DrawQuad2D();

	private:
		static void SetAPI(API api) { RendererAPI::SetAPI(api); }

		static void InitializeQuadRendering();
		static void Flush();

	private:
		struct Data
		{
			Ref<VertexArray> QuadVertexArray;
		};

		static Data* s_Data;
		friend class Application;
	};
}