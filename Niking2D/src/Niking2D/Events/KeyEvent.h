#pragma once
#include "n2pch.h"

#include "Event.h"


namespace Niking2D {
	class N2_API KeyEvent :public Event {
	public:
		inline int GetKeyCode()const { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode){}

		int m_KeyCode;
	};

	class N2_API KeyPressedEvent :public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			:KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount()const { return m_RepeatCount; }

		std::string ToString() const {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)


	protected:
		int m_RepeatCount;
	};
}