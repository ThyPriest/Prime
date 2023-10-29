
#include "pch.h"
#include "OpenGLGraphicsContext.h"
#include "glad/glad.h"

namespace Prime
{
	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window)
	{
		PRIME_ASSERT(window == NULL, "Window is null");
		m_Window = window;
	}

	void OpenGLGraphicsContext::Initialize()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PRIME_ASSERT(status != 1, "Failed to initialize Glad!");

		PRIME_ASSERT(GLVersion.major < 4, "Prime requires at least OpenGL version 4.0!");
	}

	void OpenGLGraphicsContext::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void OpenGLGraphicsContext::Info()
	{
		Logger::Info("RendererAPI: OpenGL");
		Logger::Info("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		Logger::Info("Graphics Card: {0}", (const char*)glGetString(GL_RENDERER));
		Logger::Info("Version: {0}", (const char*)glGetString(GL_VERSION));
	}
}