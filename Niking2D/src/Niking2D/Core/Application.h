#pragma once

#include "Core.h"
#include "Niking2D/Events/Event.h"
#include "Niking2D/Core/Window.h"
#include "Niking2D/Core/LayerStack.h"

#include "Niking2D/Events/ApplicationEvent.h"
#include "Niking2D/Core/Input.h"

#include "Niking2D/ImGui/ImGuiLayer.h"
#include "Niking2D/Core/Timestep.h"



namespace Niking2D {
	class N2_API Application
	{
	public:

	/*	static Application& Get() {
			static Application instance;
			return instance;
		}*/


		Application();
		~Application();

		virtual void Run();

		void OnEvent(Event& e);

		bool OnWindowClose(WindowCloseEvent& e);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);




		inline static Application& Get() {return *s_Instance;}

		inline Window& GetWindow() {return *m_Window;}


	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;
		
		float m_LastFrameTime = 0.0f;

	};

	//	To be defined in CLIENT
	Application* CreateApplication();
}

