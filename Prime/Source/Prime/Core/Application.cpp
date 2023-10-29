
#include "pch.h"
#include "Application.h"
#include "Logger.h"

namespace Prime
{
	Application::Application(ApplicationSpec& spec)
	{
		Logger::Initialize();
		Info();

		m_Spec = spec;
	}

	Application::~Application()
	{
		Logger::Shutdown();
	}

	void Application::Run()
	{
		while (m_Running)
		{

		}
	}

	void Application::Info()
	{
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
}