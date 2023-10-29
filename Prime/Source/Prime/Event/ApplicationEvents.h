#pragma once

#include "Event.h"

namespace Prime
{
	class WindowCloseEvent : public Event
	{
	public:
		static EventType GetStaticType() { return EventType::WindowClose; }

		const char* GetName() const override { return "WindowCloseEvent"; }

		EventType GetType() const override { return GetStaticType(); }
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		static EventType GetStaticType() { return EventType::WindowResize; }

		const char* GetName() const override { return "WindowResizeEvent"; }

		EventType GetType() const override { return GetStaticType(); }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

	private:
		unsigned int m_Width, m_Height;
	};
}