#include "n2pch.h"
#include "Application.h"

#include "Events/KeyEvent.h"
#include "Log.h"
#include <glad/glad.h>

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Niking2D {

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
			case Niking2D::ShaderDataType::Float:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Float2:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Float3:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Float4:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Mat3:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Mat4:		return GL_FLOAT;
			case Niking2D::ShaderDataType::Int:			return GL_INT;
			case Niking2D::ShaderDataType::Int2:		return GL_INT;
			case Niking2D::ShaderDataType::Int3:		return GL_INT;
			case Niking2D::ShaderDataType::Int4:		return GL_INT;
			case Niking2D::ShaderDataType::Bool:		return GL_BOOL;
		}
		N2_CORE_ASSERT(false, "Unkonwn ShaderDataType!");
		return 0;
	}

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

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			  0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"},
				//{ShaderDataType::Float3, "a_Normal"}
			};
			m_VertexBuffer->SetLayout(layout);
		}

		unsigned int index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout) {

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponementCount(), ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				//element.Size ,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}




		unsigned int indices[3] = {
			0,1,2
		};

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		
		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0 ) in vec3 a_Position;
			layout(location = 1 ) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragSrc = R"(
			#version 330 core
			out vec4 color;

			in vec4 v_Color;
			in vec3 v_Position;

			void main(){
				color = vec4(v_Position + 0.5 , 1.0);
				color = v_Color;
				
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
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);


			

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