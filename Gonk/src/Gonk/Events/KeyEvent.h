#pragma once

#include "Event.h"

#include "Gonk/Input/KeyCodes.h"

namespace Gonk {
	
	class GONK_API KeyEvent : public Event 
	{
	public:
		inline Key GetKeyCode() const { return m_KeyCode; }
		inline int GetScanCode() const { return m_ScanCode; }

		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)
	protected:
		KeyEvent(Key keycode, int scancode)
			: m_KeyCode(keycode), m_ScanCode(scancode) {}

		Key m_KeyCode;
		int m_ScanCode;
	};

	class GONK_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(Key keycode, int scancode, int repeatCount)
			: KeyEvent(keycode, scancode), m_RepeatCount(repeatCount) {}
		
		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << "repeats)";
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class GONK_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(Key keycode, int scancode)
			: KeyEvent(keycode, scancode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class GONK_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(unsigned int c)
			: KeyEvent((Key)c, -1) {} // TEMPORARY put scancode as -1. Surely I will never ever use scancode.

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}