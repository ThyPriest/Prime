#pragma once

#include "Core.h"
#include "Window.h"
#include "Prime/Event/Event.h"

int main(int argc, char** argv);

namespace Prime
{
	struct ApplicationSpec
	{
		std::string Title = "Prime Application", WorkingDirectory = "";
		uint32_t Width = 1000, Height = 600;
		bool Vsync = true;
		API GraphicsAPI = API::OpenGL;
	};

	class PRIME_API Application
	{
	public:
		Application(ApplicationSpec& spec);
		virtual ~Application();

		static Application& Get() { return *s_Instance; }
		Window& GetWindow() { return m_Window; }

		void Quit() { m_Running = false; }

	private:
		void Run();
		void Info();

		void SubscribeToEvent();

		void OnWindowClose(const Event& event) { Quit(); }
		void OnKeyPressed(const Event& event);
		void OnWindowResize(const Event& event);

	private:
		static Application* s_Instance;
		ApplicationSpec m_Spec;
		Window m_Window;

		bool m_Running = true;
		bool m_Minimized = false;
		friend int::main(int argc, char** argv);
	};

	Application* CreateApplication();
}