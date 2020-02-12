#pragma once
#include "n2pch.h"

#include "Event.h"

namespace Niking2D {
	class N2_API WindowResizeEvent :public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:m_Width(width), m_Height(height){}

		// Inherited via Event
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResieEvent: (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		
	private:
		unsigned int m_Width, m_Height;
	};

	class N2_API WindowCloseEvent : public Event {
	public:

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}
	};
}