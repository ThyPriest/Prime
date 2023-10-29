#pragma once

#include "Core.h"
#include <string>

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

	private:
		void Run();
		void Info();

	private:
		ApplicationSpec m_Spec;

		bool m_Running = true;
		friend int::main(int argc, char** argv);
	};

	Application* CreateApplication();
}