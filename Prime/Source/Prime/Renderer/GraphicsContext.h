#pragma once

#include "Prime/Core/Core.h"

typedef struct GLFWwindow GLFWwindow;

namespace Prime
{
	class PRIME_API GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Initialize() = 0;
		virtual void SwapBuffer() = 0;
		virtual void Info() = 0;

		static Scope<GraphicsContext> Create(GLFWwindow* window);
	};
}