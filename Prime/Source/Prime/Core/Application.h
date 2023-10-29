#pragma once

#include "Core.h"
#include "Window.h"

int main(int argc, char** argv);

namespace Prime
{
	struct ApplicationSpec
	{
		std::string Title = "Prime Application";
		uint32_t Width = 1000, Height = 600;
		bool Vsync = true;
	};

	class PRIME_API Application
	{
	public:
		Application(ApplicationSpec& spec);
		virtual ~Application();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return m_Window; }

	private:
		void Run();
		void Info();

	private:
		static Application* s_Instance;
		ApplicationSpec m_Spec;
		Window m_Window;

		bool m_Running = true;
		friend int::main(int argc, char** argv);
	};

	Application* CreateApplication();
}