
#include "pch.h"
#include "Input.h"
#include "Prime/Core/Application.h"

#define win Prime::Application::Get().GetWindow().GetWindowHandle()

namespace Prime
{
	bool Input::IsKeyPressed(KeyCode key)
	{
		auto state = glfwGetKey(win, key);
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto state = glfwGetMouseButton(win, button);
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(win, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}