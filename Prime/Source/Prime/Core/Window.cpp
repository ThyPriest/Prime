
#include "pch.h"
#include "Window.h"
#include "GLFW/glfw3.h"
#include "Prime/Event/EventSystem.h"

namespace Prime
{
	static int s_WindowCount = 0;

	static void GLFWError(int error, const char* description)
	{
		PRIME_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::Window()
	{
		m_Data.Width = 0;
		m_Data.Height = 0;
		m_Data.Vsync = true;
		m_Data.Title = "";
		m_Window = nullptr;
	}

	void Window::Initialize(std::string title, uint32_t width, uint32_t height, bool vsync)
	{
		PRIME_PROFILE_FUNCTION();

		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.Vsync = vsync;

		if (s_WindowCount == 0)
		{
			PRIME_ASSERT(glfwInit() != 1, "GLFW failed to initialized") glfwSetErrorCallback(GLFWError);
			m_Window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
			++s_WindowCount;
		}

		glfwSetWindowUserPointer(m_Window, &m_Data);
		m_GraphicsContext = GraphicsContext::Create(m_Window);
		m_GraphicsContext->Initialize();
		InitializeCallbacks();
		SetVsync(vsync);
	}

	void Window::Shutdown()
	{
		PRIME_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_WindowCount;

		if (s_WindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::SetVsync(bool vsync)
	{
		PRIME_PROFILE_FUNCTION();

		if (vsync) { glfwSwapInterval(1); }
		if (vsync == false) { glfwSwapInterval(0); }
		m_Data.Vsync = vsync;
	}

	void Window::ContextInfo()
	{
		m_GraphicsContext->Info();
	}

	void Window::Update()
	{
		PRIME_PROFILE_FUNCTION();

		glfwPollEvents();
		m_GraphicsContext->SwapBuffer();
	}

	void Window::InitializeCallbacks()
	{
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				Dispatcher::PostEvent<WindowCloseEvent>();
			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				Data& data = *(Data*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				Dispatcher::PostEvent<WindowResizeEvent>(width, height);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					Dispatcher::PostEvent<KeyPressedEvent>(key, mods, 0);
					break;
				}
				case GLFW_RELEASE:
				{
					Dispatcher::PostEvent<KeyReleasedEvent>(key);
					break;
				}
				case GLFW_REPEAT:
				{
					Dispatcher::PostEvent<KeyPressedEvent>(key, true);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				Dispatcher::PostEvent<KeyTypedEvent>(keycode);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
				{
					Dispatcher::PostEvent<MouseButtonPressedEvent>(button);
					break;
				}
				case GLFW_RELEASE:
				{
					Dispatcher::PostEvent<MouseButtonReleasedEvent>(button);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				Dispatcher::PostEvent<MouseScrolledEvent>((float)xOffset, (float)yOffset);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				Dispatcher::PostEvent<MouseMovedEvent>((float)xPos, (float)yPos);
			});
	}
}