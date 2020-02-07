#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Niking2D/Window.h"

#include "Events/ApplicationEvent.h"

namespace Niking2D {
	class N2_API Application
	{
	public:

		Application();
		~Application();

		virtual void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};



	//	To be defined in CLIENT
	Application* CreateApplication();
}

