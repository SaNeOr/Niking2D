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

		m_ImGuiLayer = new ImGuiLayer();

		PushOverLayer(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			  0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = {
			0,1,2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/*	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexSource =
			"#version 330 core\n"
			"layout(location = 0) in vec3 position;\n"\
			"void main(){\n"\
			"	gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"\
			"};";

		glShaderSource(vertex, 1, &vertexSource, nullptr);
		glCompileShader(vertex);

		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentSource =
			"#version 330 core\n"\
			"out vec4 FragColor;\n"\
			"void main(){\n"\
			"	FragColor  = vec4(1.0, 0.0, 0.0, 1.0);\n"\
			"};";

		glShaderSource(fragment, 1, &fragmentSource, nullptr);
		glCompileShader(fragment);

		m_Shader = glCreateProgram();

		glAttachShader(m_Shader, vertex);
		glAttachShader(m_Shader, fragment);
		glLinkProgram(m_Shader);

		glUseProgram(m_Shader);*/
		
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			out vec3 v_Position;
			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			
			out vec4 color;
			in vec3 v_Position;
			void main(){
				color = vec4(v_Position + 0.5 , 1.0);
				
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragSrc));

 	}



	Application::~Application()
	{

	}
	void Application::Run()
	{

		while (m_Running) {

			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


			

		/*	for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}*/

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
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* layer)
	{
		m_LayerStack.PushOverLayer(layer);
		layer->OnAttach();
	}
}

