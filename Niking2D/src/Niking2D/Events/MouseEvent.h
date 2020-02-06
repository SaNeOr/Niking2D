#pragma once

#include "Event.h"
#include <sstream>

namespace Niking2D {

	class N2_API MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(float x, float y)
			:m_MouseX(x), m_MouseY(y){}
		
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX, m_MouseY;
	};

	class N2_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float x, float y)
			:m_XOffset(x), m_YOffset(y){}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString()const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}

	private:
		float m_XOffset, m_YOffset;
	};



}
