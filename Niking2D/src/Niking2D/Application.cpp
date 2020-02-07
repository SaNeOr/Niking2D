#include "n2pch.h"
#include "Application.h"

#include "Events/KeyEvent.h"
#include "Log.h"


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Niking2D {

	Application::Application()
	{
		m_Window = (std::unique_ptr<Window>) Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		
	}
	Application::~Application()
	{

	}
	void Application::Run()
	{

		while (m_Running) {
			m_Window->OnUpdate();
		}

	}
	void Application::OnEvent(Event & e)
	{

		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		N2_CORE_TRACE("{0}", e);
	}

	bool Application::OnWindowClose(WindowCloseEvent & e)
	{
		m_Running = false;
		return true;
	}
}
