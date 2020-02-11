#pragma once
#include "Niking2D/Layer.h"

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
		float m_Time = 0.0f;

	};
}