
#include "pch.h"
#include "TerraLayer.h"

namespace Prime
{
	void TerraLayer::Attach()
	{
		m_Camera2DController = Camera2DController(1.7776);
		m_Camera2DController.SubscribeToEvents();

		AssetManager::LoadTexture2D("assets/Textures/logo.png", "Logo", Texture2D::Filter::Nearest);
	}

	void TerraLayer::Detach()
	{

	}

	void TerraLayer::Update()
	{
		m_Camera2DController.Update();
		RenderCommand::Clear();

		Renderer::BeginScene2D(m_Camera2DController.GetCamera());

		Renderer::DrawQuad2D({-.8f, .0f, .0f}, {.4f, .4f}, { 1.0f, .0f, .0f, 1.0f });
		Renderer::DrawTexture2D(AssetManager::GetTexture2D("Logo"), { .0f, .0f, .0f }, { .8f, .8f }, { 1.0f, 1.0f, 1.0f, 1.0f });

		Renderer::EndScene2D();
	}

	void TerraLayer::SubscribeToEvents()
	{

	}
}