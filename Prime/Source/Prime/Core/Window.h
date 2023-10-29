#pragma once

#include "Core.h"
#include <string>
#include "Prime/Renderer/GraphicsContext.h"

namespace Prime
{
	class PRIME_API Window
	{
	public:
		Window();
		~Window() = default;

		void Initialize(std::string title, uint32_t width, uint32_t height, bool vsync);
		void Shutdown();

		const inline uint32_t GetWidth() const { return m_Data.Width; }
		const inline uint32_t GetHeight() const { return m_Data.Height; }

		const inline bool IsVsync() const { return m_Data.Vsync; }
		void SetVsync(bool vsync);
		void ContextInfo();

		void Update();
		inline GLFWwindow* GetWindowHandle() { return m_Window; }

	private:
		void InitializeCallbacks();

	private:
		struct Data
		{
			std::string Title;
			uint32_t Width, Height;
			bool Vsync = true;
		};

		Data m_Data;
		GLFWwindow* m_Window;
		Scope<GraphicsContext> m_GraphicsContext;
	};
}