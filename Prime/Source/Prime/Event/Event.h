#pragma once

#include <string>
#include <sstream>

namespace Prime
{
	enum class EventType
	{
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	class Event
	{
	public:
		virtual ~Event() {}

		virtual const char* GetName() const = 0;

		virtual EventType GetType() const = 0;

		virtual std::string ToString() const { return GetName(); }
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}

