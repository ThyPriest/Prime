#pragma once

#include "Prime/Core/Core.h"
#include "Prime/Renderer/GraphicsContext.h"

namespace Prime
{
	class PRIME_API OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* window);

		void Initialize() override;
		void SwapBuffer() override;
		void Info() override;

	private:
		GLFWwindow* m_Window;
	};
}
