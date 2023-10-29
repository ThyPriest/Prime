#pragma once

#include "Event.h"
#include "Prime/Input/KeyCode.h"
#include "Prime/Input/ModCode.h"

namespace Prime
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, ModCode modeCode, bool isRepeat = false)
			: KeyEvent(keycode), m_ModeCode(modeCode), m_IsRepeat(isRepeat) {}

		bool IsRepeat() const { return m_IsRepeat; }

		ModCode GetKeyMods() { return m_ModeCode; }

		static EventType GetStaticType() { return EventType::KeyPressed; }

		const char* GetName() const override { return "KeyPressedEvent"; }

		EventType GetType() const override { return GetStaticType(); }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

	private:
		bool m_IsRepeat;
		ModCode m_ModeCode;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		static EventType GetStaticType() { return EventType::KeyReleased; }

		const char* GetName() const override { return "KeyReleasedEvent"; }

		EventType GetType() const override { return GetStaticType(); }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		static EventType GetStaticType() { return EventType::KeyTyped; }

		const char* GetName() const override { return "KeyTypedEvent"; }

		EventType GetType() const override { return GetStaticType(); }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	};
}
