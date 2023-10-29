
#include "pch.h"
#include "Application.h"

namespace Prime
{
	Application::Application(ApplicationSpec& spec)
	{
		m_Spec = spec;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{

		}
	}
}