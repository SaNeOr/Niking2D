#include "n2pch.h"
#include "Application.h"


#include "Niking2D/Events/KeyEvent.h"
#include "Log.h"
#include <glad/glad.h>
#include "Niking2D/Renderer/Renderer.h"
#include <GLFW/glfw3.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Niking2D {

	Application* Application::s_Instance = nullptr;



	Application::Application()
	{

		N2_PROFILE_FUNCTION();

		N2_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = (std::unique_ptr<Window>) Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_Window->SetVSync(true);

		m_ImGuiLayer = new ImGuiLayer();

		PushOverLayer(m_ImGuiLayer);
 	}

	Application::~Application()
	{
		N2_PROFILE_FUNCTION();

		
	}
	void Application::Run()
	{
		N2_PROFILE_FUNCTION();

		while (m_Running) {

			float time = (float)glfwGetTime();

			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();

  			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}

			m_ImGuiLayer->End();

			
			//auto[x, y] = Input::GetMousePosition();
			//N2_CORE_TRACE("{0}, {1}", x, y);

			//m_ImGuiLayer->Begin();
			//	for (Layer* layer : m_LayerStack) {
			//		layer->OnUpdate();
			//	}
			//m_ImGuiLayer->End();
				
			m_Window->OnUpdate();
		}

	}
	void Application::OnEvent(Event & e)
	{
		N2_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//N2_CORE_TRACE("{0}", e);

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
		N2_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		N2_PROFILE_FUNCTION();

		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}
}