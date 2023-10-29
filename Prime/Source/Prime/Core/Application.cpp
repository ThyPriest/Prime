
#include "pch.h"
#include "Application.h"
#include "Logger.h"
#include "Prime/Event/EventSystem.h"
#include "LayerStack.h"
#include "GameTime.h"
#include "Prime/Renderer/Renderer.h"
#include "AssetManager.h"

namespace Prime
{
	Application* Application::s_Instance = nullptr;

	Application::Application(ApplicationSpec& spec)
	{
		PRIME_PROFILE_FUNCTION();

		PRIME_ASSERT(s_Instance != nullptr, "Application already exist");
		s_Instance = this;

		Logger::Initialize();
		GameTime::Initialize(60);
		Renderer::SetAPI(spec.GraphicsAPI);

		Info();
		m_Spec = spec;
		m_Window.Initialize(spec.Title, spec.Width, spec.Height, spec.Vsync);
		m_Window.ContextInfo();

		Renderer::Initialize();
		RenderCommand::SetClearColor({ .2f, .2f, .2f, 1.0f });
	}

	Application::~Application()
	{
		PRIME_PROFILE_FUNCTION();

		m_Window.Shutdown();
		Dispatcher::Shutdown();
		LayerStack::Shutdown();
		GameTime::Shutdown();
		Renderer::Shutdown();
		AssetManager::Shutdown();
		Logger::Shutdown();
	}

	void Application::Run()
	{
		PRIME_PROFILE_FUNCTION();

		GameTime::Tick();
		SubscribeToEvent();

		while (m_Running)
		{
			if (!m_Minimized) { LayerStack::Update(); }
			m_Window.Update();
		}
	}

	void Application::Info()
	{
		PRIME_PROFILE_FUNCTION();

		Logger::Info("Prime {}.{}.{}", 1, 1, 0);

#ifdef PRIME_DEBUG
		Logger::Info("Configuration: DEBUG");
#endif
#ifdef PRIME_RELEASE
		Logger::Info("Configuration: RELEASE");
#endif
#ifdef PRIME_PLATFORM_WINDOWS
		Logger::Info("System: WINDOWS");
#endif
#ifdef PRIME_PLATFORM_LINUX
		Logger::Info("System: LINUX");
#endif
#ifdef PRIME_PLATFORM_MAC
		Logger::Info("System: MACOSX");
#endif
	}
	
	void Application::SubscribeToEvent()
	{
		PRIME_PROFILE_FUNCTION();

		Dispatcher::SubscribeToEvent<WindowCloseEvent>(this, &Application::OnWindowClose);
		Dispatcher::SubscribeToEvent<WindowResizeEvent>(this, &Application::OnWindowResize);
		Dispatcher::SubscribeToEvent<KeyPressedEvent>(this, &Application::OnKeyPressed);

		if (!LayerStack::IsEmpty()) { LayerStack::GetTopLayer()->SubscribeToEvents(); }
	}

	void Application::OnKeyPressed(const Event& event)
	{
		PRIME_PROFILE_FUNCTION();

		KeyPressedEvent e = Dispatcher::CastToEvent<KeyPressedEvent>(event);
		if (e.GetKeyCode() == Key::Escape) { Quit(); }
	}

	void Application::OnWindowResize(const Event& event)
	{
		PRIME_PROFILE_FUNCTION();

		WindowResizeEvent e = Dispatcher::CastToEvent<WindowResizeEvent>(event);
		RenderCommand::SetViewport(e.GetWidth(), e.GetHeight());
	}
}