#include "n2pch.h"
#include "Application.h"

#include "Events/KeyEvent.h"
#include "Log.h"
#include <glad/glad.h>


#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Niking2D {

	//static Application* Application::s_in
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		N2_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = (std::unique_ptr<Window>) Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

 	}

	Application::~Application()
	{

	}
	void Application::Run()
	{

		while (m_Running) {


			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			auto[x, y] = Input::GetMousePosition();
			N2_CORE_TRACE("{0}, {1}", x, y);

			m_Window->OnUpdate();
		}

	}
	void Application::OnEvent(Event & e)
	{

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		N2_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}
}
