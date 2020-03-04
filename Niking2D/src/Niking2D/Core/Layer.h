#pragma once

#include "Niking2D/Core/Core.h"
#include "Niking2D/Events/Event.h"
#include "Niking2D/Core/Timestep.h"

namespace Niking2D {

	class N2_API Layer {
	public:
		Layer(const std::string &name = "Layer");
		virtual ~Layer();
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}

		virtual void OnImGuiRender() {}

		virtual void OnEvent(Event & event) {}


		inline const std::string &GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};
}