
#include "pch.h"
#include "TerraLayer.h"

namespace Prime
{
	void TerraLayer::Attach()
	{
		//m_Camera2DController = Camera2DController(1.7776);
	}

	void TerraLayer::Detach()
	{

	}

	void TerraLayer::Update()
	{
		RenderCommand::Clear();

		//Renderer::BeginScene2D(m_Camera2DController.GetCamera());

		Renderer::DrawQuad2D();

		Renderer::EndScene2D();
	}

	void TerraLayer::SubscribeToEvents()
	{

	}
}