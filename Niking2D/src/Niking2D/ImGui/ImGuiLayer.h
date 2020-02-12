#pragma once
#include "Niking2D/Layer.h"
#include "Niking2D/Events/ApplicationEvent.h"
#include "Niking2D/Events/KeyEvent.h"
#include "Niking2D/Events/MouseEvent.h"

namespace Niking2D {

	class N2_API ImGuiLayer:public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent & e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent & e);
		bool OnMouseMovedEvent(MouseMovedEvent & e);
		bool OnMouseScrolledEvent(MouseScrolledEvent & e);
		bool OnKeyPressedEvent(KeyPressedEvent & e);
		bool OnKeyReleasedEvent(KeyReleasedEvent & e);
		bool OnKeyTypedEvent(KeyTypedEvent & e);
		bool OnWindowResizeEvent(WindowResizeEvent & e);

	private:
		float m_Time = 0.0f;

	};
}