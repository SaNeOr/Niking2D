#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Niking2D/Window.h"
#include "Niking2D/LayerStack.h"

#include "Events/ApplicationEvent.h"
#include "Niking2D/Input.h"

#include "Niking2D/ImGui/ImGuiLayer.h"

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




		inline static Application& Get() {
			return *s_Instance;
		}
		inline Window& GetWindow() {
			return *m_Window;
		}

	private:
		static Application* s_Instance;
		std::unique_ptr<Window> m_Window;

		ImGuiLayer* m_ImGuiLayer;

		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		
		unsigned int m_Shader;
	};



	//	To be defined in CLIENT
	Application* CreateApplication();
}

