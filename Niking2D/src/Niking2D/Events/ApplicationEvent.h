#pragma once

#include "Event.h"
#include <sstream>

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
		
	private:
		unsigned int m_Width, m_Height;
	};
}